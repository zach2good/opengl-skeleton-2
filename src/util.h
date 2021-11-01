#pragma once

#include "common.h"

struct Point
{
    Point()
     
    {
    }

    Point(std::size_t _x, std::size_t _y)
    : x((float)_x)
    , y((float)_y)
    {
    }

    float x{0.0f};
    float y{0.0f};
};

// https://www.geeksforgeeks.org/find-corners-of-rectangle-using-mid-points/
std::vector<Point> getRotatedPoints(Point p, Point q, float width)
{
    Point a;
    Point b;
    Point c;
    Point d;

    // horizontal rectangle
    if (p.x == q.x)
    {
        a.x = p.x - (width / 2.0f);
        a.y = p.y;

        d.x = p.x + (width / 2.0f);
        d.y = p.y;

        b.x = q.x - (width / 2.0f);
        b.y = q.y;

        c.x = q.x + (width / 2.0f);
        c.y = q.y;
    }

    // vertical rectangle
    else if (p.y == q.y)
    {
        a.y = p.y - (width / 2.0f);
        a.x = p.x;

        d.y = p.y + (width / 2.0f);
        d.x = p.x;

        b.y = q.y - (width / 2.0f);
        b.x = q.x;

        c.y = q.y + (width / 2.0f);
        c.x = q.x;
    }

    // slanted rectangle
    else
    {
        // calculate slope of the side
        float m = (p.x - q.x) / (q.y - p.y);

        // calculate displacements along axes
        float dx = (width / std::sqrt(1.0f + (m * m))) * 0.5f;
        float dy = m * dx;

        a.x = p.x - dx;
        a.y = p.y - dy;

        b.x = q.x - dx;
        b.y = q.y - dy;

        c.x = q.x + dx;
        c.y = q.y + dy;

        d.x = p.x + dx;
        d.y = p.y + dy;
    }

    return { a, b, c, d };
}

float normalizeWidth(std::size_t pixelPos)
{
    // Map (0 to 1280) to (-1 to 1)
    // slope = (output_end - output_start) / (input_end - input_start)
    // output = output_start + slope * (input - input_start)
    float slope = (1.0f - -1.0f) / (1280.0f - 0.0f);
    return -1.0f + slope * ((float)pixelPos - 0.0f);
}

float normalizeHeight(std::size_t pixelPos)
{
    // Map (0 to 720) to (-1 to 1)
    // slope = (output_end - output_start) / (input_end - input_start)
    // output = output_start + slope * (input - input_start)
    float slope = (1.0f - -1.0f) / (720.0f - 0.0f);
    return -1.0f + slope * ((float)pixelPos - 0.0f);
}

std::size_t pixelizeWidth(float pos)
{
    // Map (-1 to 1) to (0 to 1280)
    // slope = (output_end - output_start) / (input_end - input_start)
    // output = output_start + slope * (input - input_start)
    float slope = (1280.0f - 0.0f) / (1.0f - -1.0f);
    return 0.0f + slope * (pos - -1.0f);
}

std::size_t pixelizeHeight(float pos)
{
    // Map (-1 to 1) to (0 to 720)
    // slope = (output_end - output_start) / (input_end - input_start)
    // output = output_start + slope * (input - input_start)
    float slope = (720.0f - 0.0f) / (1.0f - -1.0f);
    return 0.0f + slope * (pos - -1.0f);
}
