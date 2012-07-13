import argparse
import os
import imp
import pylab
import matplotlib.cm as cm
import matplotlib

def is_dict_contained(d1, d2):
    """
    Takes two dicts and checks whether the keys and
    values are a subset of the other
    :return: True if d_one is contained withing d_two
    """
    assert(type(d1) == type(dict()))
    assert(type(d2) == type(dict()))

    for k in d1:
        if not k in d2:
            return False

        elif type(d1[k]) == type(dict()):
            if not is_dict_contained(d1[k], d2[k]):
                return False

        elif not d1[k] == d2[k]:
            return False

    return True

def filter_results(results, **kw):
    """
    Filter the results by matching the keyword arguments
    to the results
    :return: a list of results which match the keyword arguments
    """

    output = []

    # First we remove all results which do not match our filter
    for r in results:
        if is_dict_contained(kw, r):
            output.append(r)

    return output

def find_in_dict(d, key):
    """
    Searches the dict d and any contained dicts
    for the key
    """
    assert(type(d) == type(dict()))

    out = []

    for k in d:
        if k == key:
            out.append(d[k])
        elif type(d[k]) == type(dict()):
            out += find_in_dict(d[k], key)

    return out


def key_values(results, key):
    """
    Iterates through the list of dicts and any contained
    dicts and returns a list of values corresponding to the key
    """
    assert(type(results) == type(list()))

    out = []
    for dicts in results:
        out += find_in_dict(dicts, key)

    return out

def unique_key_values(results, key):
    """
    Returns a list of unique values with the corresponding
    key from the dict results
    """
    assert(type(results) == type(list()))

    r = key_values(results, key)
    return list(set(r))

def line_color(idx):
    """
    Takes a index and returns a color
    :return: a color value
    """
    return cm.hot(0.2+idx/10.,1)

def line_style(idx):
    """
    Some custom line dashes the (1,1) means one pixel-on
    one pixel-off in the line
    """
    if idx == 0:
        return (1,1)
    if idx == 1:
        return (1,0)
    if idx == 2:
        return (5,1,5,1)
    if idx == 3:
        return (5,1,1,1)
    if idx == 4:
        return (10,3)

    assert(0)

def line_props(idx):
    """
    Line properties
    """
    props = {}
    props['dashes'] = line_style(idx)
    props['color'] = line_color(idx)
    props['linewidth'] = 1.5
    return props



def prepare_plot_data(results, device):
    """
    Places the data in a dict (see comment below)
    """
    # Places the result in a dict with the following content
    #
    # {
    #    "device"            : "galaxy nexus",           # benchmark device
    #    "k"                 : [1,2,3,4]
    #    "block-size"        : [1000, 2000, 3000, 4000], # [KiB]
    #    "results-bitmap"    : [23.5, 43.0, 54.0, 65.3], # [ms]
    #    "error-bitmap"      : [0.56, 0.1, 2.4, 4.2],
    #    "results-binary-k1" : [23.5, 43.0, 54.0, 65.3],
    #    "error-binary-k1"   : [0.56, 0.1, 2.4, 4.2]
    #    "results-binary-k2" : [23.5, 43.0, 54.0, 65.3],
    #    "error-binary-k2"   : [0.56, 0.1, 2.4, 4.2]
    #    "results-binary-k3" : [23.5, 43.0, 54.0, 65.3],
    #    "error-binary-k3"   : [0.56, 0.1, 2.4, 4.2]
    #    "results-binary-k4" : [23.5, 43.0, 54.0, 65.3],
    #    "error-binary-k4"   : [0.56, 0.1, 2.4, 4.2]
    # }
    #

    plot_data = {}
    plot_data['device'] = device

    k_values = unique_key_values(results, "k")
    plot_data['k'] = k_values

    block_length = sorted(unique_key_values(results, "block_length"))
    block_size = list(pylab.array(block_length) / 1000) # Convert to KiB

    plot_data['block-size'] = block_size

    bitmap_results = []
    bitmap_error = []

    for b in block_length:
        r_b = filter_results(results, testcase = "Prime2325Bitmap",
                             benchmark = "FindPrefix",
                             config = {'block_length': b})


        # Should be a list of only one benchmark
        assert(len(r_b) == 1)
        d = r_b[0]

        time = pylab.array(d['data']) / 1000.0  # convert to milliseconds
        result  = pylab.mean(time)
        error = pylab.std(time, ddof = 1)

        bitmap_results.append(result)
        bitmap_error.append(error)

    plot_data['results-bitmap'] = bitmap_results
    plot_data['error-bitmap'] = bitmap_error

    for k in k_values:

        binary_results = []
        binary_error = []

        for b in block_length:

            r_b = filter_results(results, testcase = "Prime2325BinarySearch",
                                 benchmark = "FindPrefix",
                                 config = {'block_length': b, 'k': k})

            print r_b

            # Should be a list of only one benchmark
            assert(len(r_b) == 1)
            d = r_b[0]

            time = pylab.array(d['data']) / 1000.0  # convert to milliseconds
            result  = pylab.mean(time)
            error = pylab.std(time, ddof = 1)

            binary_results.append(result)
            binary_error.append(error)

        plot_data['results-binary-k%d' % k] = binary_results
        plot_data['error-binary-k%d' % k] = binary_error

    return plot_data


def plot_data(data):

    props = line_props(0)
    pylab.errorbar(data['block-size'], data['results-bitmap'],
                   yerr = data['error-bitmap'], label = 'bitmap',
                   **props)

    for k in data['k']:
        props = line_props(k)
        pylab.errorbar(data['block-size'], data['results-binary-k%d' % k],
                       yerr = data['error-binary-k%d' % k],
                       label = 'binary %d' % k, **props)

    pylab.legend(loc='upper left')
    pylab.grid(True)
    pylab.xlabel('Block size [KiB]')
    pylab.ylabel('Prefix search time [ms]')

    pylab.xlim([min(data['block-size']), max(data['block-size'])])

    #pylab.ion()
    #pylab.show()

    #import time
    #time.sleep(5)

def plot_generation_data(data):

    props = line_props(0)
    pylab.errorbar(data['block-size'], data['results-bitmap'],
                   yerr = data['error-bitmap'], label = 'bitmap',
                   **props)

    for k in data['k']:
        props = line_props(k)
        pylab.errorbar(data['block-size'], data['results-binary-k%d' % k],
                       yerr = data['error-binary-k%d' % k],
                       label = 'binary %d' % k, **props)

    pylab.legend(loc='upper left')
    pylab.grid(True)
    pylab.xlabel('Generation size [-]')
    pylab.ylabel('Prefix search time [ms]')

    symbols = [8,16,32,64,128,256,512,1024,2048]#[i+1 for i in range(7, 2047)]
    symbol_size = 1400
    symbol_sizes_bytes = pylab.array(symbols)*symbol_size
    symbol_sizes_mb = [b / 1000 for b in symbol_sizes_bytes]
    labels = [str(s) for s in symbols]
    pylab.xscale('log', basex=2)
    pylab.xticks(symbol_sizes_mb, labels)
    pylab.xlim([symbol_sizes_mb[0], symbol_sizes_mb[-1]])
    pylab.ylim([0, 40])

    #pylab.xlim([min(data['block-size']), max(data['block-size'])])

    #pylab.ion()
    #pylab.show()

    #import time
    #time.sleep(5)



def plot(resultfile):
    resultfile = os.path.expanduser(resultfile)
    resultfile = os.path.abspath(resultfile)

    result = imp.load_source('result', resultfile)

    data = prepare_plot_data(result.results, "ok")

    pylab.subplot(211)
    plot_data(data)
    pylab.subplot(212)
    plot_generation_data(data)
    pylab.show()


    print 'Saving...'
    pylab.savefig("benchmark_prefix_search.eps", bbox_inches='tight')

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--result-file', dest='resultfile', action='store',
        help='the .py file written by gauge python-printer',
        required = True)

    args = parser.parse_args()
    plot(args.resultfile)
