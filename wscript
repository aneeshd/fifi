#! /usr/bin/env python
# encoding: utf-8

import os

# Necessary since we override different Contexts
import waflib.extras.wurftools as wt

APPNAME = 'fifi'
VERSION = '1.0.1'

wt.add_dependency('boost', 'git://github.com/steinwurf/external-boost.git',
                  '1.1.1-boost_1_48_0')

wt.add_dependency('gtest', 'git://github.com/steinwurf/external-gtest.git',
                  '1.0.2-gtest_1_6_0')

wt.add_dependency('sak', 'git://github.com/steinwurf/sak.git',
                  '1.1.0')



def load_helper(ctx, name):
    if ctx.is_system_dependency(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        ctx.load_dependency(name)


def options(opt):
    opt.load('wurftools')

    load_helper(opt, 'boost')
    load_helper(opt, 'gtest')
    load_helper(opt, 'sak')



def configure(conf):

    conf.load('wurftools')

    load_helper(conf, 'boost')
    load_helper(conf, 'gtest')
    load_helper(conf, 'sak')


def build(bld):

    bld.load('wurftools')

    load_helper(bld, 'boost')
    load_helper(bld, 'gtest')
    load_helper(bld, 'sak')

    # Export own includes
    bld(includes = '.',
        export_includes = '.',
        name = 'fifi_includes')


    bld.recurse('test')
    bld.recurse('benchmark/basic_operations')
    bld.recurse('benchmark/arithmetic')


