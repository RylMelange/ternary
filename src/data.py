
GATE_WIDTH = 130
WINDOW_SIZE = (1600,900)
BACKGROUND_COLOUR = (40,36,56)
PORT_RADIUS = 7

colours = {
   -1:  (160,   0,      0),
    0:  (150,   150,    150),
    1:  (0,     0,      255),
    2:  (255,   255,    255)
}
gate_styles = { #height, input#, output#, colour
    # "input":    [240,3,3,(123,74,195)],
    "split":        [60,1,2,    (100,100,195)],
    "3split":       [90,1,3,    (100,100,195)],
    "27split":      [500,1,27,  (100,100,195)],
    "relay":        [90,4,3,    (240,190,190)],
    "buffer":       [90,4,3,    (240,140,230)],
    "min":          [60,2,1,    (200,150,230)],
    "max":          [60,2,1,    (140,240,195)],
    "sub":          [60,2,1,    (230,190,230)],
    "mux":          [530,30,1,  (100,190,195)],
    "inc":          [30,1,1,    (240,230,220)],
    "dec":          [30,1,1,    (220,230,240)],
    "mul":          [60,2,1,    (190,200,160)],
    "neg":          [30,1,1,    (90,190,90)],
    "and":          [60,2,1,    (240,190,190)],
    "ripple":       [60,2,1,    (210,190,190)],
    "3pos":         [90,3,3,    (160,190,240)],
    "half_adder":   [60,2,2,    (190,240,210)],
    "adder":        [90,3,2,    (210,240,210)],
    "sr_latch":     [90,3,1,    (200,200,190)],
    "d_latch":      [60,2,1,    (190,230,190)],
    "3reg":         [90,4,3,    (230,215,130)],
    "3mem":         [170,7,3,   (180,190,180)],
    "control":      [250,13,6,  (180,190,180)],
    "demux":        [850,4,27,  (200,215,120)],
    "out":          [30,1,0,    (190,90,90)],
    "test":         [90,3,1,    (255,0,255)],
    "dummy":        [30,1,1,    (0,0,0)]
}
