project('c-container', 'c',
    version : '0.1',
    default_options : [
        'c_std=c99',
        'warning_level=2',
    ],
)

executable('main',
    [
        'deque.c',
        'main.c',
        'vec.c',
    ],
    c_args : ['-Wpointer-arith', '-fsanitize=undefined'],
    link_args : ['-fsanitize=undefined'],
)
