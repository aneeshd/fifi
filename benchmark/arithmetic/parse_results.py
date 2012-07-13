# Takes the output xyz.py file from an arithmetic benchmark
# and produces a xyz_plot_data.py file that will contain
# data which may be plotted using plot_results.py script

import argparse
import os
import imp
import pylab


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


def prepare_plot_data(results, operation, vectors, vector_size, device):
    """
    Places the data in a dict (see comment below)
    """
    # Places the result in a dict with the following content
    #
    # {
    #    "device"         : "galaxy nexus",               # benchmark device
    #    "operation"      : "dest[i] = dest[i] + src[i]", # the operation
    #    "vectors"        : 32,                           # the # vectors
    #    "vector_size"    : 1000,                         # the vector size [B]
    #    "benchmarks"     : ["FullTable8", "LogTable8"],  # the algorithm
    #    "results-linear" : [23.5, 43,0],                 # throughput [MB/s]
    #    "error-linear"   : [0.56, 0.1]                   # standard deviation
    #    "results-random" : [23.5, 43,0],                 # throughput [MB/s]
    #    "error-random"   : [0.56, 0.1]                   # standard deviation
    # }
    #

    config = {"operation": operation,
              "vectors": vectors,
              "vector_size": vector_size}

    r = filter_results(results, config = config)

    benchmarks = sorted(unique_key_values(r, "benchmark"))
    assert(len(benchmarks) > 0)

    plot_data = {}
    plot_data['operation'] = operation
    plot_data['vectors'] = vectors
    plot_data['vector_size'] = vector_size
    plot_data['benchmarks'] = benchmarks
    plot_data['device'] = device


    # Now we have all the benchmarks contained we just have to fetch the
    # results first for linear and then for random access
    access = ['linear', 'random']

    for a in access:

        data  = []
        error = []

        r_a = filter_results(r, config = {'data_access': a})

        for b in benchmarks:
            r_a_b = filter_results(r_a, benchmark = b)

            # Should be a list of only one bechmark
            assert(len(r_a_b) == 1)
            d = r_a_b[0]

            time = d['data']
            size = vectors * vector_size

            throughtput = size / pylab.array(time)

            data.append(pylab.mean(throughtput))
            error.append(pylab.std(throughtput, ddof=1))

        plot_data['results-'+a] = data
        plot_data['error-'+a]   = error

    return plot_data


def plot_data(data):

    height = 0.40
    space  = (1.0 - 2*height) / 2
    bar_offset = height / 2

    bottom_offset = bar_offset + space
    label_offset = bottom_offset + height

    benchmarks = data['benchmarks']
    benchmarks_pos = pylab.arange(len(benchmarks))+bottom_offset    # the bar centers on the y axis

    results_linear = data['results-linear']
    results_random = data['results-random']

    error_linear = data['error-linear']
    error_random = data['error-random']

    pylab.figure()
    s = pylab.subplot(111)

    pylab.barh(benchmarks_pos,
               results_linear,
               xerr=error_linear,
               height = height,
               label = 'linear access',
               color = 'r',
               hatch = '\\',
               ecolor='r', align='center')

    pylab.barh(benchmarks_pos + height,
               results_random,
               xerr=error_linear,
               height = height,
               label = 'random access',
               ecolor='r', align='center')

    pylab.legend(bbox_to_anchor=(0.0, 1.02, 1.0, 1.0), loc=3,
                 mode="expand", ncol=2, borderaxespad=0.)

    pylab.yticks(pylab.arange(len(benchmarks)) + 0.5, benchmarks)
    pylab.xlabel('Performance [MB/s]')

    t = pylab.title('%s %s\nvectors=%d size=%d [B]' % (
        data['device'], data['operation'],
        data['vectors'], data['vector_size']), multialignment='center')

    t.set_y(1.12)

    pylab.grid(True)
    pylab.ylim([0, 8])

    # Shink current axis to make space for legend and axis text
    box = s.get_position()
    s.set_position([box.x0 * 1.90, box.y0,
                    (box.width  * 0.9),
                    (box.height * 0.9)])

def filename(vectors, vector_size, operation, device, fileext):
    operation = operation.replace('[i]','')
    operation = operation.replace('=','equal')
    operation = operation.replace('+','add')
    operation = operation.replace('-','subtract')
    operation = operation.replace('*','multiply')
    operation = operation.replace('(','')
    operation = operation.replace(')','')
    operation = operation.replace(' ','_')

    return "%s_arithmetic_%d_%d_%s.%s" % (
        device, vectors, vector_size, operation, fileext)

def plot(resultfile, vectors, vector_size, device, show, fileext):
    resultfile = os.path.expanduser(resultfile)
    resultfile = os.path.abspath(resultfile)

    vectors = int(vectors)
    vector_size = int(vector_size)

    result = imp.load_source('result', resultfile)

    operations = unique_key_values(result.results, "operation")

    for operation in operations:
        data = prepare_plot_data(
            results   = result.results,
            operation = operation,
            vectors   = vectors,
            vector_size = vector_size,
            device    = device)

        plot_data(data)

        if show:
            pylab.ion()
            pylab.show()


            raw_input("Press any Key")

        fileout = filename(vectors, vector_size, operation, device, fileext)
        print 'Saving %s...' % fileout
        pylab.savefig(fileout, bbox_inches='tight')


    return


if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--result_file', dest='resultfile', action='store',
        help='the .py file written by gauge python-printer',
        required = True)

    parser.add_argument(
        '--vectors', dest='vectors', action='store',
        help='symbols',
        required = True)

    parser.add_argument(
        '--vector_size', dest='vector_size', action='store',
        help='symbol_size',
        required = True)

    parser.add_argument(
        '--device', dest='device', action='store',
        help='device', default = None)

    parser.add_argument(
        '--show', dest='show', action='store',
        help='device', default = "unknown")

    parser.add_argument(
        '--fileext', dest='fileext', action='store',
        help='fileext', default = "eps")


    args = parser.parse_args()

    plot(resultfile = args.resultfile,
         vectors = args.vectors,
         vector_size = args.vector_size,
         device = args.device,
         show = args.show,
         fileext = args.fileext)
