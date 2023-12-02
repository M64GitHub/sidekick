
#ifndef RESID_VISUALIZER_H
#define RESID_VISUALIZER_H

#include "resid.h"

class ReSIDVisualizer
{
public:
    ReSIDVisualizer(ReSID *r, ReSIDPbData *d);
    ~ReSIDVisualizer();

    void visualize();

private:
    ReSID *R;
    ReSIDPbData *D;
};

#endif
