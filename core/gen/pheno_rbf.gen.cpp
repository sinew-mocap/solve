#include "slang_rt/slang-cpp-prelude.h"
#ifdef SLANG_PRELUDE_NAMESPACE
using namespace SLANG_PRELUDE_NAMESPACE;
#endif


#line 9 "../spec/slang/pheno_rbf.slang"
struct RbfParams_0
{
    uint32_t J_0;
};


#line 9
struct GlobalParams_0
{
    StructuredBuffer<Vector<float, 3> > v0_0;
    StructuredBuffer<uint32_t> crow_0;
    StructuredBuffer<uint32_t> col_0;
    StructuredBuffer<float> val_0;
    RWStructuredBuffer<Vector<float, 3> > jpos_0;
    RbfParams_0* params_0;
};


#line 9
struct KernelContext_0
{
    GlobalParams_0* globalParams_0;
};

void _rbf(void* _S1, void* entryPointParams_0, void* globalParams_1)
{

#line 14
    ComputeThreadVaryingInput * _S2 = (slang_bit_cast<ComputeThreadVaryingInput *>(_S1));

#line 14
    KernelContext_0 kernelContext_0;

#line 14
    (&kernelContext_0)->globalParams_0 = (slang_bit_cast<GlobalParams_0*>(globalParams_1));

    uint32_t i_0 = (_S2->groupID * Vector<uint32_t, 3> (64U, 1U, 1U) + _S2->groupThreadID).x;

    if(i_0 >= ((slang_bit_cast<GlobalParams_0*>(globalParams_1))->params_0->J_0))
    {

#line 18
        return;
    }

#line 19
    Vector<float, 3>  _S3 = (Vector<float, 3> )0.0f;

#line 19
    uint32_t k_0 = (&kernelContext_0)->globalParams_0->crow_0.Load(i_0);

#line 19
    Vector<float, 3>  acc_0 = _S3;
    for(;;)
    {

#line 20
        if(k_0 < ((&kernelContext_0)->globalParams_0->crow_0).Load(i_0 + 1U))
        {
        }
        else
        {

#line 20
            break;
        }

#line 21
        Vector<float, 3>  acc_1 = acc_0 + (Vector<float, 3> )(&kernelContext_0)->globalParams_0->val_0.Load(k_0) * (&kernelContext_0)->globalParams_0->v0_0.Load((&kernelContext_0)->globalParams_0->col_0.Load(k_0));

#line 20
        k_0 = k_0 + 1U;

#line 20
        acc_0 = acc_1;

#line 20
    }

    *(&((&kernelContext_0)->globalParams_0->jpos_0)[i_0]) = acc_0;
    return;
}

// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void rbf_Thread(ComputeThreadVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    _rbf(varyingInput, entryPointParams, globalParams);
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void rbf_Group(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    ComputeThreadVaryingInput threadInput = {};
    threadInput.groupID = varyingInput->startGroupID;
    for (uint32_t x = 0; x < 64; ++x)
    {
        threadInput.groupThreadID.x = x;
        _rbf(&threadInput, entryPointParams, globalParams);
    }
}
// [numthreads(64, 1, 1)]
SLANG_PRELUDE_EXPORT
void rbf(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
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
                rbf_Group(&groupVaryingInput, entryPointParams, globalParams);
            }
        }
    }
}
