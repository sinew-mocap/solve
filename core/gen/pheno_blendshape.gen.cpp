#include "slang_rt/slang-cpp-prelude.h"
#ifdef SLANG_PRELUDE_NAMESPACE
using namespace SLANG_PRELUDE_NAMESPACE;
#endif


#line 8 "../spec/slang/pheno_blendshape.slang"
struct BlendshapeParams_0
{
    uint32_t P_0;
    uint32_t NB_0;
};


#line 8
struct GlobalParams_0
{
    StructuredBuffer<Vector<float, 3> > templ_0;
    StructuredBuffer<Vector<float, 3> > blend_0;
    StructuredBuffer<float> coeffs_0;
    RWStructuredBuffer<Vector<float, 3> > vanny_0;
    BlendshapeParams_0* params_0;
};


#line 8
struct KernelContext_0
{
    GlobalParams_0* globalParams_0;
};

void _blendshape(void* _S1, void* entryPointParams_0, void* globalParams_1)
{

#line 13
    ComputeThreadVaryingInput * _S2 = (slang_bit_cast<ComputeThreadVaryingInput *>(_S1));

#line 13
    KernelContext_0 kernelContext_0;

#line 13
    (&kernelContext_0)->globalParams_0 = (slang_bit_cast<GlobalParams_0*>(globalParams_1));

    uint32_t p_0 = (_S2->groupID * Vector<uint32_t, 3> (64U, 1U, 1U) + _S2->groupThreadID).x;
    uint32_t P_1 = (slang_bit_cast<GlobalParams_0*>(globalParams_1))->params_0->P_0;
    uint32_t _S3 = (slang_bit_cast<GlobalParams_0*>(globalParams_1))->params_0->NB_0;
    if(p_0 >= ((slang_bit_cast<GlobalParams_0*>(globalParams_1))->params_0->P_0))
    {

#line 18
        return;
    }

#line 19
    Vector<float, 3>  _S4 = (&kernelContext_0)->globalParams_0->templ_0.Load(p_0);

#line 19
    uint32_t c_0 = 0U;

#line 19
    Vector<float, 3>  acc_0 = _S4;
    for(;;)
    {

#line 20
        if(c_0 < _S3)
        {
        }
        else
        {

#line 20
            break;
        }
        float w_0 = (&kernelContext_0)->globalParams_0->coeffs_0.Load(c_0);
        if(w_0 == 0.0f)
        {

#line 23
            c_0 = c_0 + 1U;

#line 20
            continue;
        }

#line 20
        acc_0 = acc_0 + (Vector<float, 3> )w_0 * (&kernelContext_0)->globalParams_0->blend_0.Load(c_0 * P_1 + p_0);

#line 20
        c_0 = c_0 + 1U;

#line 20
    }

#line 26
    *(&((&kernelContext_0)->globalParams_0->vanny_0)[p_0]) = acc_0;
    return;
}

// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void blendshape_Thread(ComputeThreadVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    _blendshape(varyingInput, entryPointParams, globalParams);
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void blendshape_Group(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    ComputeThreadVaryingInput threadInput = {};
    threadInput.groupID = varyingInput->startGroupID;
    for (uint32_t x = 0; x < 64; ++x)
    {
        threadInput.groupThreadID.x = x;
        _blendshape(&threadInput, entryPointParams, globalParams);
    }
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void blendshape(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    ComputeVaryingInput vi = *varyingInput;
    ComputeVaryingInput groupVaryingInput = {};
    for (uint32_t z = vi.startGroupID.z; z < vi.endGroupID.z; ++z)
    {
        groupVaryingInput.startGroupID.z = z;
        for (uint32_t y = vi.startGroupID.y; y < vi.endGroupID.y; ++y)
        {
            groupVaryingInput.startGroupID.y = y;
            for (uint32_t x = vi.startGroupID.x; x < vi.endGroupID.x; ++x)
            {
                groupVaryingInput.startGroupID.x = x;
                blendshape_Group(&groupVaryingInput, entryPointParams, globalParams);
            }
        }
    }
}
