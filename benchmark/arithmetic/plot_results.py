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

def filter_block_lenght(results):
    s = set()
    for r in results:
        s.add(r['config']['block_length'])
    return sorted(list(s))

def filter_kvalues(results):
    s = set()
    for r in results:
        s.add(r['config']['k'])
    return sorted(list(s))

def filter_bitmap(results, block_lengths):

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

    bitmap_results = filter_results(
        result.results, testcase = 'run_prime2325_bitmap')
    binary_results = filter_results(
        result.results, testcase = 'run_prime2325_binary_search')

    block_lengths = filter_block_lenght(result.results)
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
