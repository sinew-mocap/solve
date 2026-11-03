#include "slang_rt/slang-cpp-prelude.h"
#ifdef SLANG_PRELUDE_NAMESPACE
using namespace SLANG_PRELUDE_NAMESPACE;
#endif


#line 11 "../spec/slang/pheno_skeleton_fit.slang"
struct SkeletonFitParams_0
{
    uint32_t J_0;
    uint32_t V_0;
};


#line 11
struct GlobalParams_0
{
    StructuredBuffer<float> v0_0;
    StructuredBuffer<float> bsh_0;
    StructuredBuffer<float> bw_0;
    StructuredBuffer<float> jpos_0;
    StructuredBuffer<float> sw_0;
    StructuredBuffer<int32_t> parents_0;
    RWStructuredBuffer<float> outbw_0;
    SkeletonFitParams_0* params_0;
};


#line 11
struct KernelContext_0
{
    GlobalParams_0* globalParams_0;
};


#line 9152 "hlsl.meta.slang"
static float clamp_0(float x_0, float minBound_0, float maxBound_0)
{

#line 9164
    return (F32_min(((F32_max((x_0), (minBound_0)))), (maxBound_0)));
}


#line 10098
static float dot_0(Vector<float, 3>  x_1, Vector<float, 3>  y_0)
{

#line 10098
    int32_t i_0 = int(0);

#line 10098
    float result_0 = 0.0f;

#line 10117
    for(;;)
    {

#line 10117
        if(i_0 < int(3))
        {
        }
        else
        {

#line 10117
            break;
        }

#line 10118
        float result_1 = result_0 + _slang_vector_get_element(x_1, i_0) * _slang_vector_get_element(y_0, i_0);

#line 10117
        i_0 = i_0 + int(1);

#line 10117
        result_0 = result_1;

#line 10117
    }

    return result_0;
}


#line 12353
static float length_0(Vector<float, 3>  x_2)
{

#line 12365
    return (F32_sqrt((dot_0(x_2, x_2))));
}


#line 16 "../spec/slang/pheno_skeleton_fit.slang"
static Vector<float, 3>  cr_0(Vector<float, 3>  a_0, Vector<float, 3>  b_0)
{

#line 16
    float _S1 = a_0.y;

#line 16
    float _S2 = b_0.z;

#line 16
    float _S3 = a_0.z;

#line 16
    float _S4 = b_0.y;

#line 16
    float _S5 = b_0.x;

#line 16
    float _S6 = a_0.x;

#line 16
    return Vector<float, 3> (_S1 * _S2 - _S3 * _S4, _S3 * _S5 - _S6 * _S2, _S6 * _S4 - _S1 * _S5);
}


#line 18
static void mul9_0(FixedArray<float, 9>  * A_0, FixedArray<float, 9>  * B_0, FixedArray<float, 9>  * C_0)
{

#line 18
    int32_t r_0 = int(0);
    for(;;)
    {

#line 19
        if(r_0 < int(3))
        {
        }
        else
        {

#line 19
            break;
        }

#line 19
        int32_t c_0 = int(0);

#line 19
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

#line 20
            int32_t _S7 = r_0 * int(3);

#line 20
            (*C_0)[_S7 + c_0] = (*A_0)[_S7] * (*B_0)[c_0] + (*A_0)[_S7 + int(1)] * (*B_0)[int(3) + c_0] + (*A_0)[_S7 + int(2)] * (*B_0)[int(6) + c_0];

#line 19
            c_0 = c_0 + int(1);

#line 19
        }

#line 19
        r_0 = r_0 + int(1);

#line 19
    }

    return;
}


#line 22
static void rodrigues_0(Vector<float, 3>  a_1, Vector<float, 3>  b_1, FixedArray<float, 9>  * R_0)
{
    Vector<float, 3>  au_0 = a_1 / (Vector<float, 3> )(F32_max((length_0(a_1)), (9.99999993922529029e-09f)));

#line 24
    Vector<float, 3>  bu_0 = b_1 / (Vector<float, 3> )(F32_max((length_0(b_1)), (9.99999993922529029e-09f)));
    float d_0 = clamp_0(dot_0(au_0, bu_0), -1.0f, 1.0f);

#line 25
    int32_t r_1;

#line 25
    float _S8;
    if(d_0 < -0.99999898672103882f)
    {

#line 26
        Vector<float, 3>  w_0;
        if((F32_abs((bu_0.x))) > 0.60000002384185791f)
        {

#line 27
            w_0 = Vector<float, 3> (0.0f, 1.0f, 0.0f);

#line 27
        }
        else
        {

#line 27
            w_0 = Vector<float, 3> (1.0f, 0.0f, 0.0f);

#line 27
        }
        Vector<float, 3>  x_3 = cr_0(bu_0, w_0);

#line 28
        Vector<float, 3>  x_4 = x_3 / (Vector<float, 3> )length_0(x_3);

#line 28
        FixedArray<float, 3>  _S9 = { x_4.x, x_4.y, x_4.z };

#line 28
        r_1 = int(0);
        for(;;)
        {

#line 29
            if(r_1 < int(3))
            {
            }
            else
            {

#line 29
                break;
            }

#line 29
            int32_t c_1 = int(0);

#line 29
            for(;;)
            {

#line 29
                if(c_1 < int(3))
                {
                }
                else
                {

#line 29
                    break;
                }

#line 29
                float _S10 = 2.0f * _S9[r_1] * _S9[c_1];

#line 29
                if(r_1 == c_1)
                {

#line 29
                    _S8 = 1.0f;

#line 29
                }
                else
                {

#line 29
                    _S8 = 0.0f;

#line 29
                }

#line 29
                (*R_0)[r_1 * int(3) + c_1] = _S10 - _S8;

#line 29
                c_1 = c_1 + int(1);

#line 29
            }

#line 29
            r_1 = r_1 + int(1);

#line 29
        }
        return;
    }
    Vector<float, 3>  v_0 = cr_0(bu_0, au_0);
    FixedArray<float, 9>  K_0;

#line 33
    K_0[int(0)] = 0.0f;

#line 33
    float _S11 = v_0.z;

#line 33
    K_0[int(1)] = - _S11;

#line 33
    float _S12 = v_0.y;

#line 33
    K_0[int(2)] = _S12;

#line 33
    K_0[int(3)] = _S11;

#line 33
    K_0[int(4)] = 0.0f;

#line 33
    float _S13 = v_0.x;

#line 33
    K_0[int(5)] = - _S13;

#line 33
    K_0[int(6)] = - _S12;

#line 33
    K_0[int(7)] = _S13;

#line 33
    K_0[int(8)] = 0.0f;

#line 33
    FixedArray<float, 9>  _S14 = K_0;

#line 33
    FixedArray<float, 9>  _S15 = K_0;
    FixedArray<float, 9>  KK_0;

#line 34
    mul9_0(&_S14, &_S15, &KK_0);

#line 34
    float _S16 = 1.0f / (1.0f + d_0);

#line 34
    r_1 = int(0);
    for(;;)
    {

#line 35
        if(r_1 < int(9))
        {
        }
        else
        {

#line 35
            break;
        }

#line 35
        if((r_1 % int(4)) == int(0))
        {

#line 35
            _S8 = 1.0f;

#line 35
        }
        else
        {

#line 35
            _S8 = 0.0f;

#line 35
        }

#line 35
        (*R_0)[r_1] = _S8 + K_0[r_1] + _S16 * KK_0[r_1];

#line 35
        r_1 = r_1 + int(1);

#line 35
    }
    return;
}


#line 17
static float det9_0(FixedArray<float, 9>  * m_0)
{

#line 17
    return (*m_0)[int(0)] * ((*m_0)[int(4)] * (*m_0)[int(8)] - (*m_0)[int(5)] * (*m_0)[int(7)]) - (*m_0)[int(1)] * ((*m_0)[int(3)] * (*m_0)[int(8)] - (*m_0)[int(5)] * (*m_0)[int(6)]) + (*m_0)[int(2)] * ((*m_0)[int(3)] * (*m_0)[int(7)] - (*m_0)[int(4)] * (*m_0)[int(6)]);
}


#line 49
static void regularize_0(FixedArray<float, 9>  * H_0)
{

#line 49
    float scale_0 = 0.0f;

#line 49
    int32_t r_2 = int(0);

    for(;;)
    {

#line 51
        if(r_2 < int(3))
        {
        }
        else
        {

#line 51
            break;
        }

#line 51
        int32_t _S17 = r_2 * int(3);

#line 51
        float _S18 = (F32_max((scale_0), ((F32_abs(((*H_0)[_S17]))) + (F32_abs(((*H_0)[_S17 + int(1)]))) + (F32_abs(((*H_0)[_S17 + int(2)]))))));

#line 51
        int32_t _S19 = r_2 + int(1);

#line 51
        scale_0 = _S18;

#line 51
        r_2 = _S19;

#line 51
    }
    if(scale_0 < 9.99999993922529029e-09f)
    {

#line 52
        scale_0 = 9.99999993922529029e-09f;

#line 52
    }

#line 52
    FixedArray<float, 9>  _S20 = *H_0;

#line 52
    float _S21 = det9_0(&_S20);

    float add_0 = 0.05000000074505806f * clamp_0((9.99999997475242708e-07f - (F32_abs((_S21))) / (scale_0 * scale_0 * scale_0)) / 9.99999997475242708e-07f, 0.0f, 1.0f) * scale_0;
    (*H_0)[int(0)] = (*H_0)[int(0)] + add_0;

#line 55
    (*H_0)[int(4)] = (*H_0)[int(4)] + add_0;

#line 55
    (*H_0)[int(8)] = (*H_0)[int(8)] + add_0;
    return;
}


#line 37
static void ns30_0(FixedArray<float, 9>  * H_1, FixedArray<float, 9>  * R_1)
{

#line 37
    int32_t b_2;

#line 37
    float mrs_0 = 0.0f;

#line 37
    int32_t r_3 = int(0);

    for(;;)
    {

#line 39
        if(r_3 < int(3))
        {
        }
        else
        {

#line 39
            break;
        }

#line 39
        int32_t _S22 = r_3 * int(3);

#line 39
        float _S23 = (F32_max((mrs_0), ((F32_abs(((*H_1)[_S22]))) + (F32_abs(((*H_1)[_S22 + int(1)]))) + (F32_abs(((*H_1)[_S22 + int(2)]))))));

#line 39
        int32_t _S24 = r_3 + int(1);

#line 39
        mrs_0 = _S23;

#line 39
        r_3 = _S24;

#line 39
    }

#line 39
    int32_t i_1 = int(0);
    for(;;)
    {

#line 40
        if(i_1 < int(9))
        {
        }
        else
        {

#line 40
            break;
        }

#line 40
        (*R_1)[i_1] = (*H_1)[i_1] / (mrs_0 + 9.99999993922529029e-09f);

#line 40
        i_1 = i_1 + int(1);

#line 40
    }

#line 40
    int32_t it_0 = int(0);
    for(;;)
    {

#line 41
        if(it_0 < int(30))
        {
        }
        else
        {

#line 41
            break;
        }

#line 42
        FixedArray<float, 9>  RtR_0;

#line 42
        int32_t a_2 = int(0);
        for(;;)
        {

#line 43
            if(a_2 < int(3))
            {
            }
            else
            {

#line 43
                break;
            }

#line 43
            b_2 = int(0);

#line 43
            for(;;)
            {

#line 43
                if(b_2 < int(3))
                {
                }
                else
                {

#line 43
                    break;
                }

#line 43
                RtR_0[a_2 * int(3) + b_2] = (*R_1)[a_2] * (*R_1)[b_2] + (*R_1)[int(3) + a_2] * (*R_1)[int(3) + b_2] + (*R_1)[int(6) + a_2] * (*R_1)[int(6) + b_2];

#line 43
                b_2 = b_2 + int(1);

#line 43
            }

#line 43
            a_2 = a_2 + int(1);

#line 43
        }
        FixedArray<float, 9>  term_0;

#line 44
        b_2 = int(0);

#line 44
        for(;;)
        {

#line 44
            if(b_2 < int(9))
            {
            }
            else
            {

#line 44
                break;
            }

#line 44
            if((b_2 % int(4)) == int(0))
            {

#line 44
                mrs_0 = 3.0f;

#line 44
            }
            else
            {

#line 44
                mrs_0 = 0.0f;

#line 44
            }

#line 44
            term_0[b_2] = mrs_0 - RtR_0[b_2];

#line 44
            b_2 = b_2 + int(1);

#line 44
        }

#line 44
        FixedArray<float, 9>  _S25 = *R_1;

#line 44
        FixedArray<float, 9>  _S26 = term_0;
        FixedArray<float, 9>  Rn_0;

#line 45
        mul9_0(&_S25, &_S26, &Rn_0);

#line 45
        int32_t k_0 = int(0);

#line 45
        for(;;)
        {

#line 45
            if(k_0 < int(9))
            {
            }
            else
            {

#line 45
                break;
            }

#line 45
            (*R_1)[k_0] = Rn_0[k_0] * 0.5f;

#line 45
            k_0 = k_0 + int(1);

#line 45
        }

#line 41
        it_0 = it_0 + int(1);

#line 41
    }

#line 41
    FixedArray<float, 9>  _S27 = *R_1;

#line 41
    float _S28 = det9_0(&_S27);

#line 47
    if(_S28 < 0.0f)
    {

#line 47
        (*R_1)[int(2)] = - (*R_1)[int(2)];

#line 47
        (*R_1)[int(5)] = - (*R_1)[int(5)];

#line 47
        (*R_1)[int(8)] = - (*R_1)[int(8)];

#line 47
    }
    return;
}


#line 57
static bool valid9_0(FixedArray<float, 9>  * R_2)
{

#line 57
    float _S29 = det9_0(R_2);

#line 57
    bool _S30;

    if(_S29 > 0.0f)
    {

#line 59
        _S30 = (F32_abs((_S29 - 1.0f))) <= 0.00999999977648258f;

#line 59
    }
    else
    {

#line 59
        _S30 = false;

#line 59
    }

#line 59
    if(!_S30)
    {

#line 59
        return false;
    }

#line 59
    float e_0 = 0.0f;

#line 59
    int32_t i_2 = int(0);

    for(;;)
    {

#line 61
        if(i_2 < int(3))
        {
        }
        else
        {

#line 61
            break;
        }

#line 61
        int32_t j_0 = int(0);

#line 61
        for(;;)
        {

#line 61
            if(j_0 < int(3))
            {
            }
            else
            {

#line 61
                break;
            }

#line 61
            float _S31 = (*R_2)[i_2] * (*R_2)[j_0] + (*R_2)[int(3) + i_2] * (*R_2)[int(3) + j_0] + (*R_2)[int(6) + i_2] * (*R_2)[int(6) + j_0];

#line 61
            float _S32;

#line 61
            if(i_2 == j_0)
            {

#line 61
                _S32 = 1.0f;

#line 61
            }
            else
            {

#line 61
                _S32 = 0.0f;

#line 61
            }

#line 61
            float _S33 = (F32_max((e_0), ((F32_abs((_S31 - _S32))))));

#line 61
            int32_t _S34 = j_0 + int(1);

#line 61
            e_0 = _S33;

#line 61
            j_0 = _S34;

#line 61
        }

#line 61
        i_2 = i_2 + int(1);

#line 61
    }
    return e_0 <= 0.00999999977648258f;
}


#line 64
static void jacobi9_0(FixedArray<float, 9>  * Ain_0, FixedArray<float, 3>  * w_1, FixedArray<float, 9>  * V_1)
{

#line 65
    FixedArray<float, 9>  A_1;

#line 65
    int32_t i_3 = int(0);

#line 65
    for(;;)
    {

#line 65
        if(i_3 < int(9))
        {
        }
        else
        {

#line 65
            break;
        }

#line 65
        A_1[i_3] = (*Ain_0)[i_3];

#line 65
        i_3 = i_3 + int(1);

#line 65
    }

#line 65
    i_3 = int(0);
    for(;;)
    {

#line 66
        if(i_3 < int(9))
        {
        }
        else
        {

#line 66
            break;
        }

#line 66
        float _S35;

#line 66
        if((i_3 % int(4)) == int(0))
        {

#line 66
            _S35 = 1.0f;

#line 66
        }
        else
        {

#line 66
            _S35 = 0.0f;

#line 66
        }

#line 66
        (*V_1)[i_3] = _S35;

#line 66
        i_3 = i_3 + int(1);

#line 66
    }
    FixedArray<int32_t, 3>  pp_0;

#line 67
    pp_0[int(0)] = int(0);

#line 67
    pp_0[int(1)] = int(0);

#line 67
    pp_0[int(2)] = int(1);

#line 67
    FixedArray<int32_t, 3>  qq_0;

#line 67
    qq_0[int(0)] = int(1);

#line 67
    qq_0[int(1)] = int(2);

#line 67
    qq_0[int(2)] = int(2);

#line 67
    int32_t sweep_0 = int(0);
    for(;;)
    {

#line 68
        if(sweep_0 < int(50))
        {
        }
        else
        {

#line 68
            break;
        }

#line 69
        if(((F32_abs((A_1[int(1)]))) + (F32_abs((A_1[int(2)]))) + (F32_abs((A_1[int(5)])))) < 9.99999968265522539e-21f)
        {

#line 69
            break;
        }

#line 69
        int32_t k_1 = int(0);
        for(;;)
        {

#line 70
            if(k_1 < int(3))
            {
            }
            else
            {

#line 70
                break;
            }

#line 71
            int32_t p_0 = pp_0[k_1];

#line 71
            int32_t q_0 = qq_0[k_1];

#line 71
            int32_t _S36 = pp_0[k_1] * int(3);

#line 71
            float apq_0 = A_1[_S36 + qq_0[k_1]];
            if((F32_abs((A_1[_S36 + qq_0[k_1]]))) < 9.99999968265522539e-21f)
            {

#line 72
                k_1 = k_1 + int(1);

#line 70
                continue;
            }

            int32_t _S37 = q_0 * int(3);

#line 73
            float phi_0 = 0.5f * (F32_atan2((2.0f * apq_0), (A_1[_S37 + q_0] - A_1[_S36 + p_0])));

#line 73
            float _S38 = (F32_cos((phi_0)));

#line 73
            float _S39 = (F32_sin((phi_0)));

#line 73
            i_3 = int(0);
            for(;;)
            {

#line 74
                if(i_3 < int(3))
                {
                }
                else
                {

#line 74
                    break;
                }

#line 74
                int32_t _S40 = i_3 * int(3);

#line 74
                float aip_0 = A_1[_S40 + p_0];

#line 74
                float aiq_0 = A_1[_S40 + q_0];

#line 74
                A_1[_S40 + p_0] = _S38 * A_1[_S40 + p_0] - _S39 * A_1[_S40 + q_0];

#line 74
                A_1[_S40 + q_0] = _S39 * aip_0 + _S38 * aiq_0;

#line 74
                i_3 = i_3 + int(1);

#line 74
            }

#line 74
            int32_t i_4 = int(0);
            for(;;)
            {

#line 75
                if(i_4 < int(3))
                {
                }
                else
                {

#line 75
                    break;
                }

#line 75
                float api_0 = A_1[_S36 + i_4];

#line 75
                float aqi_0 = A_1[_S37 + i_4];

#line 75
                A_1[_S36 + i_4] = _S38 * A_1[_S36 + i_4] - _S39 * A_1[_S37 + i_4];

#line 75
                A_1[_S37 + i_4] = _S39 * api_0 + _S38 * aqi_0;

#line 75
                i_4 = i_4 + int(1);

#line 75
            }

#line 75
            int32_t i_5 = int(0);
            for(;;)
            {

#line 76
                if(i_5 < int(3))
                {
                }
                else
                {

#line 76
                    break;
                }

#line 76
                int32_t _S41 = i_5 * int(3);

#line 76
                float vip_0 = (*V_1)[_S41 + p_0];

#line 76
                float viq_0 = (*V_1)[_S41 + q_0];

#line 76
                (*V_1)[_S41 + p_0] = _S38 * (*V_1)[_S41 + p_0] - _S39 * (*V_1)[_S41 + q_0];

#line 76
                (*V_1)[_S41 + q_0] = _S39 * vip_0 + _S38 * viq_0;

#line 76
                i_5 = i_5 + int(1);

#line 76
            }

#line 70
            k_1 = k_1 + int(1);

#line 70
        }

#line 68
        sweep_0 = sweep_0 + int(1);

#line 68
    }

#line 79
    (*w_1)[int(0)] = A_1[int(0)];

#line 79
    (*w_1)[int(1)] = A_1[int(4)];

#line 79
    (*w_1)[int(2)] = A_1[int(8)];
    return;
}


#line 81
static void kabsch_0(FixedArray<float, 9>  * H_2, FixedArray<float, 9>  * R_3)
{

#line 81
    int32_t j_1;

#line 81
    int32_t b_3;

#line 81
    float sc_0;
    FixedArray<float, 9>  S_0;

#line 82
    int32_t i_6 = int(0);

#line 82
    for(;;)
    {

#line 82
        if(i_6 < int(3))
        {
        }
        else
        {

#line 82
            break;
        }

#line 82
        j_1 = int(0);

#line 82
        for(;;)
        {

#line 82
            if(j_1 < int(3))
            {
            }
            else
            {

#line 82
                break;
            }

#line 82
            S_0[i_6 * int(3) + j_1] = (*H_2)[i_6] * (*H_2)[j_1] + (*H_2)[int(3) + i_6] * (*H_2)[int(3) + j_1] + (*H_2)[int(6) + i_6] * (*H_2)[int(6) + j_1];

#line 82
            j_1 = j_1 + int(1);

#line 82
        }

#line 82
        i_6 = i_6 + int(1);

#line 82
    }

#line 82
    FixedArray<float, 9>  _S42 = S_0;
    FixedArray<float, 3>  w_2;

#line 83
    FixedArray<float, 9>  Vc_0;

#line 83
    jacobi9_0(&_S42, &w_2, &Vc_0);
    FixedArray<int32_t, 3>  ord_0;

#line 84
    ord_0[int(0)] = int(0);

#line 84
    ord_0[int(1)] = int(1);

#line 84
    ord_0[int(2)] = int(2);

#line 84
    int32_t a_3 = int(0);
    for(;;)
    {

#line 85
        if(a_3 < int(3))
        {
        }
        else
        {

#line 85
            break;
        }

#line 85
        int32_t _S43 = a_3 + int(1);

#line 85
        b_3 = _S43;

#line 85
        for(;;)
        {

#line 85
            if(b_3 < int(3))
            {
            }
            else
            {

#line 85
                break;
            }

#line 85
            if((w_2[ord_0[b_3]]) > w_2[ord_0[a_3]])
            {

#line 85
                int32_t t_0 = ord_0[a_3];

#line 85
                ord_0[a_3] = ord_0[b_3];

#line 85
                ord_0[b_3] = t_0;

#line 85
            }

#line 85
            b_3 = b_3 + int(1);

#line 85
        }

#line 85
        a_3 = _S43;

#line 85
    }
    FixedArray<float, 9>  V_2;

#line 86
    FixedArray<float, 3>  sig_0;

#line 86
    b_3 = int(0);
    for(;;)
    {

#line 87
        if(b_3 < int(3))
        {
        }
        else
        {

#line 87
            break;
        }

#line 87
        sig_0[b_3] = (F32_sqrt(((F32_max((w_2[ord_0[b_3]]), (0.0f))))));

#line 87
        j_1 = int(0);

#line 87
        for(;;)
        {

#line 87
            if(j_1 < int(3))
            {
            }
            else
            {

#line 87
                break;
            }

#line 87
            int32_t _S44 = j_1 * int(3);

#line 87
            V_2[_S44 + b_3] = Vc_0[_S44 + ord_0[b_3]];

#line 87
            j_1 = j_1 + int(1);

#line 87
        }

#line 87
        b_3 = b_3 + int(1);

#line 87
    }
    FixedArray<float, 9>  U_0;

#line 88
    b_3 = int(0);
    for(;;)
    {

#line 89
        if(b_3 < int(3))
        {
        }
        else
        {

#line 89
            break;
        }

#line 90
        int32_t _S45 = int(3) + b_3;

#line 90
        int32_t _S46 = int(6) + b_3;

#line 90
        float _S47 = (*H_2)[int(0)] * V_2[b_3] + (*H_2)[int(1)] * V_2[_S45] + (*H_2)[int(2)] * V_2[_S46];

#line 90
        float _S48 = (*H_2)[int(3)] * V_2[b_3] + (*H_2)[int(4)] * V_2[_S45] + (*H_2)[int(5)] * V_2[_S46];

#line 90
        float _S49 = (*H_2)[int(6)] * V_2[b_3] + (*H_2)[int(7)] * V_2[_S45] + (*H_2)[int(8)] * V_2[_S46];
        if((sig_0[b_3]) > 9.999999960041972e-13f)
        {

#line 91
            sc_0 = 1.0f / sig_0[b_3];

#line 91
        }
        else
        {

#line 91
            sc_0 = 0.0f;

#line 91
        }

#line 91
        U_0[b_3] = _S47 * sc_0;

#line 91
        U_0[_S45] = _S48 * sc_0;

#line 91
        U_0[_S46] = _S49 * sc_0;

#line 89
        b_3 = b_3 + int(1);

#line 89
    }

#line 89
    b_3 = int(0);



    for(;;)
    {

#line 93
        if(b_3 < int(3))
        {
        }
        else
        {

#line 93
            break;
        }

#line 93
        if((sig_0[b_3]) <= 9.999999960041972e-13f)
        {

#line 94
            int32_t a_4 = (b_3 + int(1)) % int(3);

#line 94
            int32_t b_4 = (b_3 + int(2)) % int(3);
            Vector<float, 3>  uc_0 = cr_0(Vector<float, 3> (U_0[a_4], U_0[int(3) + a_4], U_0[int(6) + a_4]), Vector<float, 3> (U_0[b_4], U_0[int(3) + b_4], U_0[int(6) + b_4]));

#line 95
            U_0[b_3] = uc_0.x;

#line 95
            U_0[int(3) + b_3] = uc_0.y;

#line 95
            U_0[int(6) + b_3] = uc_0.z;

#line 93
        }

#line 93
        b_3 = b_3 + int(1);

#line 93
    }



    FixedArray<float, 9>  Vt_0;

#line 97
    i_6 = int(0);

#line 97
    for(;;)
    {

#line 97
        if(i_6 < int(3))
        {
        }
        else
        {

#line 97
            break;
        }

#line 97
        j_1 = int(0);

#line 97
        for(;;)
        {

#line 97
            if(j_1 < int(3))
            {
            }
            else
            {

#line 97
                break;
            }

#line 97
            Vt_0[i_6 * int(3) + j_1] = V_2[j_1 * int(3) + i_6];

#line 97
            j_1 = j_1 + int(1);

#line 97
        }

#line 97
        i_6 = i_6 + int(1);

#line 97
    }

#line 97
    FixedArray<float, 9>  _S50 = U_0;

#line 97
    FixedArray<float, 9>  _S51 = Vt_0;
    FixedArray<float, 9>  UVt_0;

#line 98
    mul9_0(&_S50, &_S51, &UVt_0);

#line 98
    FixedArray<float, 9>  _S52 = UVt_0;

#line 98
    float _S53 = det9_0(&_S52);

#line 98
    if(_S53 < 0.0f)
    {

#line 98
        sc_0 = -1.0f;

#line 98
    }
    else
    {

#line 98
        sc_0 = 1.0f;

#line 98
    }
    FixedArray<float, 9>  Ud_0;

#line 99
    i_6 = int(0);

#line 99
    for(;;)
    {

#line 99
        if(i_6 < int(9))
        {
        }
        else
        {

#line 99
            break;
        }

#line 99
        Ud_0[i_6] = U_0[i_6];

#line 99
        i_6 = i_6 + int(1);

#line 99
    }

#line 99
    Ud_0[int(2)] = Ud_0[int(2)] * sc_0;

#line 99
    Ud_0[int(5)] = Ud_0[int(5)] * sc_0;

#line 99
    Ud_0[int(8)] = Ud_0[int(8)] * sc_0;

#line 99
    FixedArray<float, 9>  _S54 = Ud_0;

#line 99
    FixedArray<float, 9>  _S55 = Vt_0;

#line 99
    mul9_0(&_S54, &_S55, R_3);

    return;
}


#line 102
static void finishAlign_0(FixedArray<float, 9>  * Hin_0, int32_t N_0, Vector<float, 3>  a0_0, Vector<float, 3>  a1_0, Vector<float, 3>  b0_0, Vector<float, 3>  b1_0, FixedArray<float, 9>  * R_4)
{

#line 103
    if(N_0 == int(1))
    {

#line 103
        rodrigues_0(a0_0, b0_0, R_4);

#line 103
        return;
    }

#line 104
    FixedArray<float, 9>  H_3;

#line 104
    int32_t i_7 = int(0);

#line 104
    for(;;)
    {

#line 104
        if(i_7 < int(9))
        {
        }
        else
        {

#line 104
            break;
        }

#line 104
        H_3[i_7] = (*Hin_0)[i_7];

#line 104
        i_7 = i_7 + int(1);

#line 104
    }
    Vector<float, 3>  ns_0 = cr_0(a0_0, a1_0);

#line 105
    Vector<float, 3>  nd_0 = cr_0(b0_0, b1_0);

#line 105
    float ln_0 = length_0(ns_0);

#line 105
    float ld_0 = length_0(nd_0);

#line 105
    bool _S56;
    if(ln_0 > 9.99999971718068537e-10f)
    {

#line 106
        _S56 = ld_0 > 9.99999971718068537e-10f;

#line 106
    }
    else
    {

#line 106
        _S56 = false;

#line 106
    }

#line 106
    if(_S56)
    {

#line 107
        Vector<float, 3>  vs_0 = ns_0 * (Vector<float, 3> )(length_0(a0_0) / (ln_0 + 9.99999993922529029e-09f));

#line 107
        FixedArray<float, 3>  vsa_0;

#line 107
        vsa_0[int(0)] = vs_0.x;

#line 107
        vsa_0[int(1)] = vs_0.y;

#line 107
        vsa_0[int(2)] = vs_0.z;
        Vector<float, 3>  vd_0 = nd_0 * (Vector<float, 3> )(length_0(b0_0) / (ld_0 + 9.99999993922529029e-09f));

#line 108
        FixedArray<float, 3>  vda_0;

#line 108
        vda_0[int(0)] = vd_0.x;

#line 108
        vda_0[int(1)] = vd_0.y;

#line 108
        vda_0[int(2)] = vd_0.z;

#line 108
        i_7 = int(0);
        for(;;)
        {

#line 109
            if(i_7 < int(3))
            {
            }
            else
            {

#line 109
                break;
            }

#line 109
            int32_t j_2 = int(0);

#line 109
            for(;;)
            {

#line 109
                if(j_2 < int(3))
                {
                }
                else
                {

#line 109
                    break;
                }

#line 109
                H_3[i_7 * int(3) + j_2] = H_3[i_7 * int(3) + j_2] + vsa_0[i_7] * vda_0[j_2];

#line 109
                j_2 = j_2 + int(1);

#line 109
            }

#line 109
            i_7 = i_7 + int(1);

#line 109
        }

#line 106
    }

#line 111
    regularize_0(&H_3);

#line 111
    FixedArray<float, 9>  _S57 = H_3;

#line 111
    ns30_0(&_S57, R_4);

#line 111
    FixedArray<float, 9>  _S58 = *R_4;

#line 111
    bool _S59 = valid9_0(&_S58);

#line 111
    if(!_S59)
    {

#line 111
        FixedArray<float, 9>  _S60 = H_3;

#line 111
        kabsch_0(&_S60, R_4);

#line 111
    }
    return;
}


void _skeleton_fit(void* _S61, void* entryPointParams_0, void* globalParams_1)
{

#line 116
    int32_t k_2;

#line 116
    int32_t a_5;

#line 116
    int32_t b_5;

#line 116
    Vector<float, 3>  sa0_0;

#line 116
    Vector<float, 3>  sa1_0;

#line 116
    Vector<float, 3>  sb0_0;

#line 116
    Vector<float, 3>  sb1_0;

#line 116
    ComputeThreadVaryingInput * _S62 = (slang_bit_cast<ComputeThreadVaryingInput *>(_S61));

#line 116
    KernelContext_0 kernelContext_0;

#line 116
    (&kernelContext_0)->globalParams_0 = (slang_bit_cast<GlobalParams_0*>(globalParams_1));

    if(((_S62->groupID + _S62->groupThreadID).x) != 0U)
    {

#line 118
        return;
    }

#line 119
    uint32_t _S63 = (&kernelContext_0)->globalParams_0->params_0->J_0;
    uint32_t _S64 = (&kernelContext_0)->globalParams_0->params_0->V_0;

#line 120
    uint32_t j_3 = 0U;
    for(;;)
    {

#line 121
        if(j_3 < _S63)
        {
        }
        else
        {

#line 121
            break;
        }

#line 121
        k_2 = int(0);

#line 121
        for(;;)
        {

#line 121
            if(k_2 < int(9))
            {
            }
            else
            {

#line 121
                break;
            }

#line 121
            uint32_t _S65 = j_3 * 16U + uint32_t(k_2 / int(3) * int(4)) + uint32_t(k_2 % int(3));

#line 121
            *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S65]) = (&kernelContext_0)->globalParams_0->bw_0.Load(_S65);

#line 121
            k_2 = k_2 + int(1);

#line 121
        }

#line 121
        j_3 = j_3 + 1U;

#line 121
    }

#line 121
    uint32_t i_8 = 1U;
    for(;;)
    {

#line 122
        if(i_8 < _S63)
        {
        }
        else
        {

#line 122
            break;
        }

#line 123
        int32_t _S66 = (&kernelContext_0)->globalParams_0->parents_0.Load(i_8);
        FixedArray<int32_t, 32>  ch_0;

#line 124
        j_3 = 0U;

#line 124
        int32_t nc_0 = int(0);
        for(;;)
        {

#line 125
            if(j_3 < _S63)
            {
            }
            else
            {

#line 125
                break;
            }

#line 125
            int32_t _S67 = int32_t(i_8);

#line 125
            bool _S68;

#line 125
            if(((&kernelContext_0)->globalParams_0->parents_0).Load(j_3) == _S67)
            {

#line 125
                _S68 = int32_t(j_3) != _S67;

#line 125
            }
            else
            {

#line 125
                _S68 = false;

#line 125
            }

#line 125
            if(_S68)
            {

#line 125
                if(nc_0 < int(32))
                {

#line 125
                    ch_0[nc_0] = int32_t(j_3);

#line 125
                    k_2 = nc_0 + int(1);

#line 125
                }
                else
                {

#line 125
                    k_2 = nc_0;

#line 125
                }

#line 125
                nc_0 = k_2;

#line 125
            }

#line 125
            j_3 = j_3 + 1U;

#line 125
        }
        if(nc_0 == int(0))
        {

#line 126
            k_2 = int(0);

#line 126
            for(;;)
            {

#line 126
                if(k_2 < int(9))
                {
                }
                else
                {

#line 126
                    break;
                }

#line 126
                int32_t c_2 = k_2 % int(3);

#line 126
                int32_t _S69 = k_2 / int(3) * int(4);

#line 126
                *(&((&kernelContext_0)->globalParams_0->outbw_0)[i_8 * 16U + uint32_t(_S69) + uint32_t(c_2)]) = *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S66 * int(16) + _S69 + c_2]);

#line 126
                k_2 = k_2 + int(1);

#line 126
            }

#line 126
            i_8 = i_8 + 1U;

#line 122
            continue;
        }



        uint32_t _S70 = i_8 * 16U;

#line 127
        float _S71 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S70 + 3U);

#line 127
        float _S72 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S70 + 7U);

#line 127
        float _S73 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S70 + 11U);
        uint32_t _S74 = i_8 * 3U;

#line 128
        float _S75 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S74);

#line 128
        float _S76 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S74 + 1U);

#line 128
        float _S77 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S74 + 2U);
        FixedArray<float, 9>  Hs_0;

#line 129
        k_2 = int(0);

#line 129
        for(;;)
        {

#line 129
            if(k_2 < int(9))
            {
            }
            else
            {

#line 129
                break;
            }

#line 129
            Hs_0[k_2] = 0.0f;

#line 129
            k_2 = k_2 + int(1);

#line 129
        }
        Vector<float, 3>  _S78 = Vector<float, 3> (0.0f, 0.0f, 0.0f);

#line 130
        Vector<float, 3>  sa0_1 = _S78;

#line 130
        Vector<float, 3>  sa1_1 = _S78;

#line 130
        Vector<float, 3>  sb0_1 = _S78;

#line 130
        Vector<float, 3>  sb1_1 = _S78;

#line 130
        uint32_t v_1 = 0U;

#line 130
        int32_t cnt_0 = int(0);
        for(;;)
        {

#line 131
            if(v_1 < _S64)
            {
            }
            else
            {

#line 131
                break;
            }

#line 132
            if(((&kernelContext_0)->globalParams_0->sw_0).Load(v_1 * _S63 + i_8) <= 0.00999999977648258f)
            {

#line 132
                v_1 = v_1 + 1U;

#line 131
                continue;
            }
            uint32_t _S79 = v_1 * 3U;

#line 133
            float _S80 = (&kernelContext_0)->globalParams_0->v0_0.Load(_S79) - _S75;

#line 133
            uint32_t _S81 = _S79 + 1U;

#line 133
            float _S82 = (&kernelContext_0)->globalParams_0->v0_0.Load(_S81) - _S76;

#line 133
            uint32_t _S83 = _S79 + 2U;

#line 133
            float _S84 = (&kernelContext_0)->globalParams_0->v0_0.Load(_S83) - _S77;

#line 133
            Vector<float, 3>  tg_0 = Vector<float, 3> (_S80, _S82, _S84);
            float _S85 = (&kernelContext_0)->globalParams_0->bsh_0.Load(_S79) - _S71;

#line 134
            float _S86 = (&kernelContext_0)->globalParams_0->bsh_0.Load(_S81) - _S72;

#line 134
            float _S87 = (&kernelContext_0)->globalParams_0->bsh_0.Load(_S83) - _S73;

#line 134
            Vector<float, 3>  og_0 = Vector<float, 3> (_S85, _S86, _S87);
            FixedArray<float, 3>  _S88 = { _S80, _S82, _S84 };

#line 135
            FixedArray<float, 3>  _S89 = { _S85, _S86, _S87 };

#line 135
            a_5 = int(0);
            for(;;)
            {

#line 136
                if(a_5 < int(3))
                {
                }
                else
                {

#line 136
                    break;
                }

#line 136
                b_5 = int(0);

#line 136
                for(;;)
                {

#line 136
                    if(b_5 < int(3))
                    {
                    }
                    else
                    {

#line 136
                        break;
                    }

#line 136
                    Hs_0[a_5 * int(3) + b_5] = Hs_0[a_5 * int(3) + b_5] + _S88[a_5] * _S89[b_5];

#line 136
                    b_5 = b_5 + int(1);

#line 136
                }

#line 136
                a_5 = a_5 + int(1);

#line 136
            }
            if(cnt_0 == int(0))
            {

#line 137
                sa0_0 = tg_0;

#line 137
                sa1_0 = sa1_1;

#line 137
                sb0_0 = og_0;

#line 137
                sb1_0 = sb1_1;

#line 137
            }
            else
            {

#line 137
                if(cnt_0 == int(1))
                {

#line 137
                    sa0_0 = tg_0;

#line 137
                    sa1_0 = og_0;

#line 137
                }
                else
                {

#line 137
                    sa0_0 = sa1_1;

#line 137
                    sa1_0 = sb1_1;

#line 137
                }

#line 130
                Vector<float, 3>  _S90 = sa0_0;

#line 130
                Vector<float, 3>  _S91 = sa1_0;

#line 130
                sa0_0 = sa0_1;

#line 130
                sa1_0 = _S90;

#line 130
                sb0_0 = sb0_1;

#line 130
                sb1_0 = _S91;

#line 137
            }

#line 137
            int32_t _S92 = cnt_0 + int(1);

#line 137
            sa0_1 = sa0_0;

#line 137
            sa1_1 = sa1_0;

#line 137
            sb0_1 = sb0_0;

#line 137
            sb1_1 = sb1_0;

#line 137
            cnt_0 = _S92;

#line 131
            v_1 = v_1 + 1U;

#line 131
        }

#line 131
        FixedArray<float, 9>  _S93 = Hs_0;

#line 139
        FixedArray<float, 9>  Rinit_0;

#line 139
        finishAlign_0(&_S93, cnt_0, sa0_1, sa1_1, sb0_1, sb1_1, &Rinit_0);
        FixedArray<float, 9>  Hc_0;

#line 140
        int32_t k_3 = int(0);

#line 140
        for(;;)
        {

#line 140
            if(k_3 < int(9))
            {
            }
            else
            {

#line 140
                break;
            }

#line 140
            Hc_0[k_3] = 0.0f;

#line 140
            k_3 = k_3 + int(1);

#line 140
        }

#line 140
        sa0_0 = _S78;

#line 140
        sa1_0 = _S78;

#line 140
        sb0_0 = _S78;

#line 140
        sb1_0 = _S78;

#line 140
        int32_t c_3 = int(0);

        for(;;)
        {

#line 142
            if(c_3 < nc_0)
            {
            }
            else
            {

#line 142
                break;
            }
            int32_t _S94 = ch_0[c_3] * int(16);

#line 144
            float _S95 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S94 + int(3)) - _S71;

#line 144
            float _S96 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S94 + int(7)) - _S72;

#line 144
            float _S97 = (&kernelContext_0)->globalParams_0->bw_0.Load(_S94 + int(11)) - _S73;
            float _S98 = Rinit_0[int(0)] * _S95 + Rinit_0[int(1)] * _S96 + Rinit_0[int(2)] * _S97;

#line 145
            float _S99 = Rinit_0[int(3)] * _S95 + Rinit_0[int(4)] * _S96 + Rinit_0[int(5)] * _S97;

#line 145
            float _S100 = Rinit_0[int(6)] * _S95 + Rinit_0[int(7)] * _S96 + Rinit_0[int(8)] * _S97;

#line 145
            Vector<float, 3>  pco_0 = Vector<float, 3> (_S98, _S99, _S100);
            int32_t _S101 = ch_0[c_3] * int(3);

#line 146
            float _S102 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S101) - _S75;

#line 146
            float _S103 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S101 + int(1)) - _S76;

#line 146
            float _S104 = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S101 + int(2)) - _S77;

#line 146
            Vector<float, 3>  pcn_0 = Vector<float, 3> (_S102, _S103, _S104);
            FixedArray<float, 3>  _S105 = { _S102, _S103, _S104 };

#line 147
            FixedArray<float, 3>  _S106 = { _S98, _S99, _S100 };

#line 147
            a_5 = int(0);
            for(;;)
            {

#line 148
                if(a_5 < int(3))
                {
                }
                else
                {

#line 148
                    break;
                }

#line 148
                b_5 = int(0);

#line 148
                for(;;)
                {

#line 148
                    if(b_5 < int(3))
                    {
                    }
                    else
                    {

#line 148
                        break;
                    }

#line 148
                    Hc_0[a_5 * int(3) + b_5] = Hc_0[a_5 * int(3) + b_5] + _S105[a_5] * _S106[b_5];

#line 148
                    b_5 = b_5 + int(1);

#line 148
                }

#line 148
                a_5 = a_5 + int(1);

#line 148
            }
            if(c_3 == int(0))
            {

#line 149
                sa0_0 = pcn_0;

#line 149
                sb0_0 = pco_0;

#line 149
            }
            else
            {

#line 149
                Vector<float, 3>  ca1_0;

#line 149
                Vector<float, 3>  cb1_0;

#line 149
                if(c_3 == int(1))
                {

#line 149
                    ca1_0 = pcn_0;

#line 149
                    cb1_0 = pco_0;

#line 149
                }
                else
                {

#line 149
                    ca1_0 = sa1_0;

#line 149
                    cb1_0 = sb1_0;

#line 149
                }

#line 149
                sa1_0 = ca1_0;

#line 149
                sb1_0 = cb1_0;

#line 149
            }

#line 142
            c_3 = c_3 + int(1);

#line 142
        }

#line 142
        FixedArray<float, 9>  _S107 = Hc_0;

#line 151
        FixedArray<float, 9>  Arot_0;

#line 151
        finishAlign_0(&_S107, nc_0, sa0_0, sa1_0, sb0_0, sb1_0, &Arot_0);
        FixedArray<float, 9>  R0_0;

#line 152
        a_5 = int(0);

#line 152
        for(;;)
        {

#line 152
            if(a_5 < int(9))
            {
            }
            else
            {

#line 152
                break;
            }

#line 152
            R0_0[a_5] = *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S70 + uint32_t(a_5 / int(3) * int(4)) + uint32_t(a_5 % int(3))]);

#line 152
            a_5 = a_5 + int(1);

#line 152
        }

#line 152
        FixedArray<float, 9>  _S108 = Arot_0;

#line 152
        FixedArray<float, 9>  _S109 = Rinit_0;
        FixedArray<float, 9>  tmp_0;

#line 153
        mul9_0(&_S108, &_S109, &tmp_0);

#line 153
        FixedArray<float, 9>  _S110 = tmp_0;

#line 153
        FixedArray<float, 9>  _S111 = R0_0;

#line 153
        FixedArray<float, 9>  Ri_0;

#line 153
        mul9_0(&_S110, &_S111, &Ri_0);

#line 153
        b_5 = int(0);
        for(;;)
        {

#line 154
            if(b_5 < int(9))
            {
            }
            else
            {

#line 154
                break;
            }

#line 154
            *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S70 + uint32_t(b_5 / int(3) * int(4)) + uint32_t(b_5 % int(3))]) = Ri_0[b_5];

#line 154
            b_5 = b_5 + int(1);

#line 154
        }

#line 122
        i_8 = i_8 + 1U;

#line 122
    }

#line 122
    j_3 = 0U;

#line 156
    for(;;)
    {

#line 156
        if(j_3 < _S63)
        {
        }
        else
        {

#line 156
            break;
        }

#line 157
        uint32_t _S112 = j_3 * 16U;

#line 157
        uint32_t _S113 = j_3 * 3U;

#line 157
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 3U]) = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S113);

#line 157
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 7U]) = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S113 + 1U);

#line 157
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 11U]) = (&kernelContext_0)->globalParams_0->jpos_0.Load(_S113 + 2U);
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 12U]) = 0.0f;

#line 158
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 13U]) = 0.0f;

#line 158
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 14U]) = 0.0f;

#line 158
        *(&((&kernelContext_0)->globalParams_0->outbw_0)[_S112 + 15U]) = 1.0f;

#line 156
        j_3 = j_3 + 1U;

#line 156
    }



    return;
}

// [numthreads(1, 1, 1)]
SLANG_PRELUDE_EXPORT
void skeleton_fit_Thread(ComputeThreadVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    _skeleton_fit(varyingInput, entryPointParams, globalParams);
}
// [numthreads(1, 1, 1)]
SLANG_PRELUDE_EXPORT
void skeleton_fit_Group(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
{
    ComputeThreadVaryingInput threadInput = {};
    threadInput.groupID = varyingInput->startGroupID;
    _skeleton_fit(&threadInput, entryPointParams, globalParams);
}
// [numthreads(1, 1, 1)]
SLANG_PRELUDE_EXPORT
void skeleton_fit(ComputeVaryingInput* varyingInput, void* entryPointParams, void* globalParams)
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
                skeleton_fit_Group(&groupVaryingInput, entryPointParams, globalParams);
            }
        }
    }
}
