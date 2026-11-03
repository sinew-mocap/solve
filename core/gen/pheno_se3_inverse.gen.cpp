#include "slang_rt/slang-cpp-prelude.h"
#ifdef SLANG_PRELUDE_NAMESPACE
using namespace SLANG_PRELUDE_NAMESPACE;
#endif


#line 6 "../spec/slang/pheno_se3_inverse.slang"
struct Se3InverseParams_0
{
    uint32_t J_0;
};


#line 6
struct GlobalParams_0
{
    StructuredBuffer<float> bw_0;
    RWStructuredBuffer<float> inv_0;
    Se3InverseParams_0* params_0;
};


#line 6
struct KernelContext_0
{
    GlobalParams_0* globalParams_0;
};

void _se3_inverse(void* _S1, void* entryPointParams_0, void* globalParams_1)
{

#line 11
    ComputeThreadVaryingInput * _S2 = (slang_bit_cast<ComputeThreadVaryingInput *>(_S1));

#line 11
    KernelContext_0 kernelContext_0;

#line 11
    (&kernelContext_0)->globalParams_0 = (slang_bit_cast<GlobalParams_0*>(globalParams_1));

    uint32_t j_0 = (_S2->groupID * Vector<uint32_t, 3> (64U, 1U, 1U) + _S2->groupThreadID).x;

    if(j_0 >= ((slang_bit_cast<GlobalParams_0*>(globalParams_1))->params_0->J_0))
    {

#line 15
        return;
    }

#line 16
    uint32_t o_0 = j_0 * 16U;
    float _S3 = (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + 3U);

#line 17
    float _S4 = (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + 7U);

#line 17
    float _S5 = (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + 11U);

#line 17
    int32_t r_0 = int(0);
    for(;;)
    {

#line 18
        if(r_0 < int(3))
        {
        }
        else
        {

#line 18
            break;
        }

#line 18
        int32_t c_0 = int(0);
        for(;;)
        {

#line 19
            if(c_0 < int(3))
            {
            }
            else
            {

#line 19
                break;
            }

#line 19
            *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + uint32_t(r_0 * int(4)) + uint32_t(c_0)]) = (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + uint32_t(c_0 * int(4)) + uint32_t(r_0));

#line 19
            c_0 = c_0 + int(1);

#line 19
        }
        uint32_t _S6 = uint32_t(r_0);

#line 20
        *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + uint32_t(r_0 * int(4)) + 3U]) = - ((&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + _S6) * _S3 + (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + 4U + _S6) * _S4 + (&kernelContext_0)->globalParams_0->bw_0.Load(o_0 + 8U + _S6) * _S5);

#line 18
        r_0 = r_0 + int(1);

#line 18
    }



    *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + 12U]) = 0.0f;

#line 22
    *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + 13U]) = 0.0f;

#line 22
    *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + 14U]) = 0.0f;

#line 22
    *(&((&kernelContext_0)->globalParams_0->inv_0)[o_0 + 15U]) = 1.0f;
    return;
}

// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void se3_inverse_Thread(ComputeThreadVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    _se3_inverse(varyingInput, entryPointParams, globalParams);
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void se3_inverse_Group(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    ComputeThreadVaryingInput threadInput = {};
    threadInput.groupID = varyingInput->startGroupID;
    for (uint32_t x = 0; x < 64; ++x)
    {
        threadInput.groupThreadID.x = x;
        _se3_inverse(&threadInput, entryPointParams, globalParams);
    }
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void se3_inverse(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
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
                se3_inverse_Group(&groupVaryingInput, entryPointParams, globalParams);
            }
        }
    }
}
