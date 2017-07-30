{
  'variables': {},
  'includes': [],
  'target_defaults': {
    'include_dirs': ['../lib'], # Allows using include paths relative to src/ dir.
    "cflags": [
      "-std=c++11", # Allow C++11 features.
    ],
  },

  'targets': [

    # XXX library examples
    ## Base - static library.
    #{
    #  'target_name': 'libbase',
    #  'type': 'static_library',
    #  'sources': ['base/macros.h'],
    #},
    #
    ## Shapes - static library. Uses base library.
    #{
    #  'target_name': 'libshapes',
    #  'type': 'static_library',
    #  'dependencies': ['libbase'],
    #  'sources':[
    #    'shapes/rect.cc',
    #    'shapes/rect.h',
    #    'shapes/circle.cc',
    #    'shapes/circle.h',
    #  ],
    #},

    # Area - executable. Uses base and shapes library.
    {
      'target_name': 'test',
      'type': 'executable',
      'dependencies': [],
      'sources': ['test.cc'],
    },

  ], # targets

}
