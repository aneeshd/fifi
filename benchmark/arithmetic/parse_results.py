# Takes the output xyz.py file from an arithmetic benchmark
# and produces a xyz_plot_data.py file that will contain
# data which may be plotted using plot_results.py script

import argparse
import os
import imp
import pylab

def filter_results(results, **kw):

    output = []

    for r in results:
        for k in kw:
            if not k in r: break
            elif r[k] != kw[k]: break
        else:
            output.append(r)

    return output

def filter_config(results, key):
    s = set()
    for r in results:
        s.add(r['config'][key])
    return sorted(list(s))



def filter_vector_lenght(results, block_lengths):

    out = []
    for b in block_lengths:
        for r in results:
            if b == r['config']['block_length']:
                out.append(pylab.mean(r['data']))
                break

    return out

def filter_binary(results, block_lengths, k):

    out = []
    for b in block_lengths:
        for r in results:
            if b == r['config']['block_length']:
                if k == r['config']['k']:
                    out.append(pylab.mean(r['data']))
                    break

    return out

def plot(resultfile):
    resultfile = os.path.expanduser(resultfile)
    resultfile = os.path.abspath(resultfile)

    result = imp.load_source('result', resultfile)

    operations = filter_config(result.results, 'operation')
    vector_length = filter_config(result.results, 'vector_length')
    vectors = filter_config(result.results, 'vectors')

    config_results = []
    for l in vector_length:
        for v in vectors:
            for o in operations:

                r = result.results
                r = filter(lambda b: b['config']['vector_length'] == l, r)
                r = filter(lambda b: b['config']['vectors'] == v, r)
                r = filter(lambda b: b['config']['operation'] == o, r)

                def unique_benchmarks(results):
                    s = set()
                    for r in results:
                        s.add(r['benchmark'])
                    return sorted(list(s))

                benchmarks = unique_benchmarks(r)
                data = []
                error = []

                for b in benchmarks:
                    d = filter_results(r, benchmark = b)
                    assert(len(d) == 1)
                    # The data list is the time it took to process the vectors
                    # since there is a difference from algorithm to algorithm
                    # in the size of the vector elements we calculate a MB/s

                    time = d[0]['data']
                    size = l * v * d[0]['config']['element_size']

                    #size / 1000000.0 MB
                    #time / 1000000.0 S

                    throughtput = size / pylab.array(time)

                    data.append(pylab.mean(throughtput))
                    error.append(pylab.std(throughtput, ddof=1))

                config = {'vector_length':l, 'vectors':v, 'operation': o}
                config['benchmark'] = benchmarks
                config['results'] = data
                config['error'] = error
                config_results.append(config)

    def plot(c):
        val = c['results']
        pos = pylab.arange(len(val))+.5    # the bar centers on the y axis

        pylab.figure()
        pylab.barh(pos, val, xerr=c['error'], ecolor='r', align='center')
        pylab.yticks(pos, c['benchmark'])
        pylab.xlabel('Performance [MB/s]')
        pylab.title('%s vectors=%d length=%d' % (c['operation'], c['vectors'], c['vector_length']))
        pylab.grid(True)

        #figure(2)
        #barh(pos,val, xerr=rand(5), ecolor='r', align='center')
        #yticks(pos, ('Tom', 'Dick', 'Harry', 'Slim', 'Jim'))
        #xlabel('Performance')


    #for c in config_results:
    #    plot(c)

    what = filter_results(config_results, operation = "random dest[i] = dest[i] + (constant * src[i])")
    for c in what:
        plot(c)


    pylab.show()

    print len(config_results)
    print config_results[0]
    print config_results[1]

    #print(operations, vector_length, vectors)
    return
    kvalues = filter_kvalues(binary_results)

    bitmap_out = filter_bitmap(bitmap_results, block_lengths)
    binary_out = {}
    for k in kvalues:
        binary_out[k] = filter_binary(binary_results, block_lengths, k)

    pylab.plot(block_lengths, bitmap_out, label = 'bitmap')

    for k in kvalues:
        pylab.plot(block_lengths, binary_out[k], label = 'binary %d' % k)

    pylab.legend(loc='upper left')

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
