{
  'variables': {},
  'includes': [],
  'target_defaults': {
    'include_dirs': ['../lib'], # Allows using include paths relative to src/ dir.
    'cflags': [
      '-std=c++11', # Allow C++11 features.
    ],
  },

  'targets': [
    {
      'target_name': 'tcp',
      'type': 'executable',
      'dependencies': [],
      'sources': ['tcp.cpp'],
      'cflags!': [
        '-std=c++11'
      ],
      'conditions': [
          ['OS=="win"', {
            'cflags': [
              '/WX',
            ],
          }, { # OS != "win"
            'cflags': [
              '-std=c++11',
            ],
          }],
        ]
    },

  ], # targets

}
