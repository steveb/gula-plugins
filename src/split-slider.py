#! /usr/bin/env python

import aggdraw
from PIL import Image
import sys

width = 115
knob_rad = 20
knob_dia = knob_rad * 2
knob_rim_color = (255, 255, 255)
knob_int_color = (0, 0, 0)
knob_ind_color = (128, 128, 128)
point_rad = 4
point_dia = point_rad * 2
height = 69 * 3
positions = 90
line_width = 3.0
hline_width = line_width / 2.0

line_color = (1, 211, 98, 255)
alpha = 180
spread_colors = [
    (1, 150, 242),
    (6, 236, 144),
    (255, 123, 250),
    (254, 162, 0)
]

image_width = width * positions
image_height = height + knob_dia


def draw_split_slider(im, i, fade=False):
    d = aggdraw.Draw(im)
    p = aggdraw.Pen(line_color, 3)

    off_x = i * width
    split = i / positions

    off_y = point_dia

    x_inc = width / 3
    y1 = off_y + height / 2
    y2 = off_y + (height * split) - 2
    x1 = off_x + point_rad + 2
    x2 = off_x + width - point_rad - 2
    p_rad = point_rad

    if fade:
        x1, x2 = x2, x1
        x_inc = -x_inc
        p_rad = -p_rad

    d.arc((x1 - p_rad, y1 - p_rad, x1 + p_rad, y1 + p_rad),
          0, 360, p)
    d.arc((x2 - p_rad, y2 - p_rad, x2 + p_rad, y2 + p_rad),
          0, 360, p)
    d.line([x1 + p_rad, y1, x1 + x_inc, y1, x2 - x_inc, y2, x2 - p_rad, y2], p)
    draw_knob(d, i)
    d.flush()

def draw_knob(d, i):
    p_rim = aggdraw.Pen(knob_rim_color, 3)
    b_int = aggdraw.Brush(knob_int_color)
    p_ind = aggdraw.Pen(knob_ind_color, 3)
    b_ind = aggdraw.Brush(knob_ind_color)

    i_norm = i / positions

    angle1 = 225 - 270 * i_norm
    angle2 = angle1 + 1

    x = (i * width) + (width / 2)
    y = image_height - knob_rad - 3
    kr = knob_rad
    ki = knob_rad - 15

    d.ellipse((x - kr, y - kr, x + kr, y + kr),
              p_rim, b_int)
    d.pieslice((x - kr, y - kr, x + kr, y + kr),
               angle1, angle2, p_ind)
    d.ellipse((x - ki, y - ki, x + ki, y + ki),
              p_ind, b_ind)

def gain(split, spread, origin):
    if spread == 0.0:
        spread = 0.05
    if spread >= 1.0:
        hspread_comp = 0.0
    else:
        hspread_comp = 0.5 - (spread / 2.0)

    if split > origin:
        down_start = origin + hspread_comp
        down_end = down_start + spread
        g = 1.0 + (-1.0 / (down_end - down_start)) * (split - down_start)
    else:
        up_end = origin - hspread_comp
        up_start = up_end - spread
        g = (1.0 / (up_end - up_start)) * (split - up_start)
    g = max(0.0, min(1.0, g))
    return g

def draw_spread_slider(im, fade=False):
    d = aggdraw.Draw(im)
    for i in range(positions):
        for origin in range(4):
            draw_spread_gain(d, i, origin, fade=fade)
        draw_knob(d, i)
    d.flush()

def draw_spread_gain(d, i, origin, fade=False):
    spread = (i * 4) / positions
    p = aggdraw.Pen(spread_colors[origin], 3)
    off_x = i * width - 1
    off_y = point_rad + 2

    line = []
    inner_width = width - 4
    for y in range(int(-point_rad), int(height + point_rad)):
        yp = y + off_y
        split = (y * 3) / height
        g = gain(split, spread, origin)
        if g > 0.0 and g <= 1.0:
            if fade:
                x = (g * inner_width) + 2
                if x < width * 0.25:
                    x = None
            else:
                x = width - (g * inner_width)
                if x > width * 0.75:
                    x = None
            if x:
                xp = x + off_x
                point = (xp, yp)
                line.extend(point)
    d.line(line, p)

    if fade:
        x_point = off_x + point_rad + 3
    else:
        x_point = off_x + width - point_rad - 2
    y_point = (origin / 3) * height + off_y
    d.arc((x_point - point_rad, y_point - point_rad, x_point + point_rad, y_point + point_rad),
          0, 360, p)

def main():

    args = sys.argv[1:]
    if 'split-slider.png' in args:
        im = Image.new('RGBA', (image_width, image_height), (255,255,255,0))
        for i in range(positions):
            draw_split_slider(im, i)
        im.save('split-slider.png', 'PNG', optimize=True)

    if 'spread-slider.png' in args:
        im = Image.new('RGBA', (image_width, image_height), (255, 255, 255, 0))
        draw_spread_slider(im)
        im.save('spread-slider.png', 'PNG', optimize=True)

    if 'fade-slider.png' in args:
        im = Image.new('RGBA', (image_width, image_height), (255,255,255,0))
        for i in range(positions):
            draw_split_slider(im, i, fade=True)
        im.save('fade-slider.png', 'PNG', optimize=True)

    if 'fade-spread-slider.png' in args:
        im = Image.new('RGBA', (image_width, image_height), (255, 255, 255, 0))
        draw_spread_slider(im, fade=True)
        im.save('fade-spread-slider.png', 'PNG', optimize=True)

if __name__ == "__main__":
    main()