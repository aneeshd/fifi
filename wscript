#! /usr/bin/env python
# encoding: utf-8

import os


import waflib
from waflib.ConfigSet import ConfigSet

import waflib.extras.dependency_context
import waflib.extras.toolchain_configuration_context

APPNAME = 'fifi'
VERSION = '0.9'

def options(opt):
    opt.load('toolchain_cxx')
    opt.add_dependency('gtest_1_6_0')
    opt.add_dependency('boost_1_48_0')

def configure(conf):

    conf.msg('Dependencies bundled', conf.list_bundle())

    conf.load('toolchain_cxx')
    
    conf.recurse_dependencies()
    conf.check_dependencies()

def build(bld):

    bld(includes = '.',
        export_includes = '.',
        name = 'fifi')

    bld.recurse_dependencies()
    bld.recurse('test')
    #bld.recurse('benchmark/basic_operations')
    bld.recurse('benchmark/arithmetic')
    
    
