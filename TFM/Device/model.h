#pragma once
#include <cstdarg>
#include "WString.h"

namespace Eloquent
{
    namespace ML
    {
        namespace Port
        {
            class SVM
            {
            public:
                /**
                 * Predict class for features vector
                 */
                int predict(float *x) const
                {
                    float kernels[23] = {0};
                    kernels[0] = compute_kernel(x, -0.48, -0.16, -0.53, -0.3, 0.0, -0.14, 0.0, 1.13, -0.88, 0.51, -0.58, 0.33, 0.0, -2.49, 4.6, -3.54, -1.1, 2.99, -2.57, 3.43, -2.19, 0.77, 0.0, -0.84, -1.75, 0.0, 0.93, -1.91, 0.97, -1.97, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.91, 0.0, 0.0, -0.81, 0.0, 0.0, 0.0, -0.64, -0.6, 0.0, -0.51, 0.0, 0.0, -0.37, 0.0, 0.0, 0.0, -0.22, 0.0, -0.16, 0.0, 0.0, -0.1, -0.09, -0.08, 0.0);
                    kernels[1] = compute_kernel(x, -0.48, 0.08, 0.53, 0.7, -0.35, -0.27, -0.48, 1.31, -0.22, 0.76, -0.58, -0.66, -2.6, -3.32, -0.92, -2.53, 0.55, -2.39, -0.64, 6.18, -5.83, 0.0, -4.04, 5.07, -1.75, -4.53, 6.53, -7.64, -0.97, 5.91, -3.98, -1.0, 0.0, -3.98, 1.97, -0.97, 0.95, 0.0, 1.81, -2.63, 0.84, -1.62, -0.77, 0.0, -0.69, -0.64, -0.6, -0.55, -0.51, -0.46, 0.0, -0.37, 0.0, 0.0, -0.25, -0.22, -0.19, 0.0, 0.0, -0.12, -0.1, -0.09, -0.08, 0.0);
                    kernels[2] = compute_kernel(x, -0.32, 0.49, -0.8, 0.5, 0.58, 0.0, -0.32, 0.56, 0.44, 0.25, 1.74, -0.66, -1.12, -2.91, 0.0, -3.03, 3.86, -2.99, 0.64, -4.81, 5.83, -6.93, 0.0, 4.22, -5.26, 0.0, 3.73, 0.95, -0.97, -0.99, -1.99, -4.0, 1.0, 0.0, -1.97, 0.0, -1.91, 0.93, -0.91, -0.88, 0.0, -0.81, 0.0, 0.0, 0.0, -0.64, 0.0, 0.0, -0.51, -0.46, -0.42, 0.0, 0.0, 0.0, -0.25, 0.0, -0.19, -0.16, 0.0, -0.12, -0.1, 0.0, 0.0, -0.08);
                    kernels[3] = compute_kernel(x, -0.32, 0.33, -0.53, 0.7, -0.58, -0.68, 1.28, -1.31, -0.22, -0.76, -0.58, 1.65, -1.12, 0.83, 0.0, 0.0, -1.1, 0.0, 0.0, 0.0, 0.0, -1.54, 0.0, 0.0, -0.88, -0.91, 0.0, -0.95, -0.97, 0.0, 0.0, -1.0, 0.0, -0.99, 0.0, 0.0, 0.0, -0.93, 0.0, 0.0, -0.84, -0.81, -0.77, 0.0, -0.69, 0.0, -0.6, 0.0, -0.51, 0.0, 0.0, -0.37, 0.0, 0.0, 0.0, -0.22, -0.19, 0.0, -0.14, -0.12, 0.0, 0.0, 0.0, 0.0);
                    kernels[4] = compute_kernel(x, -0.4, 0.16, 0.36, -0.2, 0.46, 0.14, 0.0, -0.56, -0.88, 0.0, 0.0, 1.98, 0.37, -3.32, 0.92, -2.53, 3.86, -4.78, 1.93, 0.69, -1.46, 1.54, -3.23, 1.69, -0.88, 0.91, 0.0, -1.91, -0.97, 0.99, 0.0, -3.0, 1.0, -0.99, 0.99, -1.94, 0.0, 0.93, -0.91, 0.0, -0.84, -0.81, -0.77, 0.0, -0.69, -0.64, 0.0, 0.0, -0.51, -0.46, -0.42, 0.0, -0.33, 0.0, -0.25, 0.0, -0.19, 0.0, 0.0, 0.0, 0.0, -0.09, -0.08, -0.08);
                    kernels[5] = compute_kernel(x, -0.32, 0.08, -0.09, -0.4, 0.35, -0.41, 0.16, 0.0, 0.44, -0.76, 0.29, -0.66, 0.37, 0.0, -0.46, 0.0, 0.0, 0.0, -0.64, 0.0, -0.73, -0.77, -0.81, 0.0, -0.88, 0.0, -0.93, -0.95, -0.97, 0.0, -0.99, 0.0, -1.0, 0.0, -0.99, -0.97, 0.0, 0.0, -0.91, 0.0, 0.0, 0.0, -0.77, -0.73, 0.0, 0.0, -0.6, 0.0, -0.51, 0.0, 0.0, -0.37, -0.33, -0.29, -0.25, -0.22, 0.0, -0.16, 0.0, -0.12, 0.0, -0.09, -0.08, -0.08);
                    kernels[6] = compute_kernel(x, -0.16, 0.33, -0.09, 0.1, -0.7, 1.63, -1.6, 0.19, 1.09, -1.01, -1.16, 0.0, 0.37, -0.42, 0.46, 1.01, -1.65, 0.0, -0.64, -0.69, 0.0, -0.77, 0.81, -0.84, 0.0, -0.91, 0.0, -0.95, -0.97, -0.99, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.95, 0.0, -0.91, -0.88, -0.84, -0.81, 0.0, 0.0, 0.0, -0.64, 0.0, -0.55, 0.0, 0.0, 0.0, 0.0, -0.33, -0.29, 0.0, -0.22, -0.19, 0.0, -0.14, 0.0, -0.1, 0.0, 0.0, -0.08);
                    kernels[7] = compute_kernel(x, -0.24, 0.25, 0.09, -0.2, 0.0, -0.14, 0.16, -0.38, 0.0, 0.25, -0.58, 0.33, -0.37, 0.0, -0.46, 0.0, -0.55, -0.6, 0.0, 0.0, 0.0, 0.0, -0.81, 0.0, -0.88, 0.0, 0.0, 0.0, 0.0, 0.0, -0.99, 0.0, -1.0, -0.99, 0.0, -0.97, -0.95, 0.0, 0.0, -0.88, 0.0, 0.0, 0.0, 0.0, 0.0, -0.64, -0.6, 0.0, -0.51, -0.46, -0.42, 0.0, -0.33, -0.29, 0.0, -0.22, 0.0, -0.16, 0.0, -0.12, 0.0, -0.09, 0.0, -0.08);
                    kernels[8] = compute_kernel(x, -0.24, 0.08, 0.0, 0.9, -0.81, 0.0, -0.96, 0.19, 0.0, 1.01, -2.61, -0.33, -1.49, -0.83, 0.46, 1.01, 0.55, 0.6, 0.0, -1.37, 2.19, 4.62, -6.47, 0.0, -4.39, 7.25, -4.66, -2.86, 5.83, -9.86, 1.99, 3.0, -5.0, 0.0, -2.96, 0.0, 0.95, -2.8, 0.91, -0.88, 0.84, -2.43, 0.0, 0.0, -0.69, 0.0, -0.6, 0.0, -0.51, 0.0, 0.0, -0.37, -0.33, -0.29, 0.0, -0.22, -0.19, -0.16, -0.14, 0.0, -0.1, 0.0, 0.0, -0.08);
                    kernels[9] = compute_kernel(x, -0.32, 0.25, -0.09, -0.5, 0.7, -0.27, 0.0, -0.94, -0.22, 0.25, -0.29, 1.32, -1.12, 0.42, -0.92, 0.51, -0.55, 0.0, 0.0, -0.69, 0.0, -0.77, 0.0, 0.0, 0.0, -0.91, 0.0, 0.0, -0.97, -0.99, -0.99, 0.0, -1.0, -0.99, -0.99, -0.97, -0.95, -0.93, 0.0, -0.88, 0.0, -0.81, 0.0, 0.0, 0.0, 0.0, 0.0, -0.55, 0.0, -0.46, -0.42, 0.0, -0.33, -0.29, -0.25, -0.22, -0.19, 0.0, 0.0, -0.12, 0.0, 0.0, -0.08, -0.08);
                    kernels[10] = compute_kernel(x, -0.4, -0.08, 0.45, 0.2, 0.0, -0.14, -1.28, -0.19, 0.0, 0.0, 1.16, -0.66, 0.0, 1.25, -2.76, 1.52, -2.76, 2.39, 0.0, -0.69, -0.73, -0.77, -2.43, 1.69, -0.88, -0.91, 1.87, -1.91, 0.97, -1.97, 0.0, 1.0, -2.0, 0.0, -0.99, 0.0, 0.0, 0.0, -0.91, -0.88, 0.0, -0.81, 0.0, -0.73, -0.69, -0.64, 0.0, -0.55, 0.0, 0.0, 0.0, 0.0, -0.33, -0.29, 0.0, 0.0, 0.0, -0.16, -0.14, -0.12, 0.0, -0.09, 0.0, -0.08);
                    kernels[11] = compute_kernel(x, -0.4, -0.58, 1.52, -1.0, -2.44, -0.41, -2.24, -1.13, 1.09, -1.27, -4.07, 0.33, -4.46, -0.83, -6.9, -5.06, -6.07, -7.17, -1.93, 1.37, -2.92, 0.0, -3.23, 9.29, 3.51, -9.07, 0.93, 5.73, -15.56, -8.87, -2.98, -5.0, -2.0, 0.99, -1.97, -0.97, 0.95, -0.93, 0.0, -0.88, 0.0, 0.0, -0.77, 0.0, -0.69, 0.0, -0.6, 0.0, 0.0, 0.0, 0.0, -0.37, 0.0, 0.0, -0.25, -0.22, 0.0, 0.0, -0.14, 0.0, -0.1, -0.09, -0.08, 0.0);
                    kernels[12] = compute_kernel(x, -0.56, -0.16, 1.96, 0.1, 1.05, 0.82, -0.32, 0.56, 1.97, -0.76, 1.16, 1.32, 2.23, 4.57, 7.36, 5.06, 1.65, -2.99, 0.0, 0.69, 2.19, -10.78, -8.89, 5.91, -3.51, -11.79, 8.39, 1.91, 1.94, 2.96, 0.99, -2.0, 2.0, -1.99, -0.99, -0.97, -0.95, 0.0, -0.91, 0.0, -0.84, -0.81, 0.0, 0.0, 0.0, 0.0, -0.6, 0.0, 0.0, -0.46, 0.0, -0.37, 0.0, 0.0, -0.25, 0.0, 0.0, -0.16, 0.0, 0.0, -0.1, 0.0, -0.08, -0.08);
                    kernels[13] = compute_kernel(x, -0.4, -0.33, -0.45, -1.0, 0.46, 0.14, 1.76, -1.69, -0.22, 3.8, 0.58, 0.66, -2.23, -1.25, -1.38, -3.54, 0.55, 5.37, -6.42, 11.67, 5.1, 6.16, -6.47, -4.22, -5.26, 4.53, -3.73, 4.77, -16.53, 7.89, 10.94, -5.0, 2.0, -6.96, 3.94, -3.89, -3.82, -0.93, -0.91, 0.88, -1.69, 0.0, -0.77, -0.73, 0.0, -0.64, 0.0, 0.0, 0.0, -0.46, -0.42, -0.37, -0.33, -0.29, -0.25, 0.0, -0.19, -0.16, -0.14, -0.12, -0.1, -0.09, -0.08, -0.08);
                    kernels[14] = compute_kernel(x, -0.48, 0.0, 0.18, -1.31, 1.39, 0.68, 0.48, -1.31, 1.75, 0.0, 2.32, 0.99, -3.72, 2.08, -5.06, 5.06, 7.72, 1.19, 1.28, 4.12, -2.92, -1.54, 4.85, 3.38, -8.77, 4.53, 0.93, -14.32, -9.72, -7.89, 3.98, 3.0, 0.0, 0.0, 1.97, -0.97, 0.0, 0.0, 0.0, -0.88, 0.0, -0.81, 0.0, 0.0, -0.69, -0.64, 0.0, 0.0, 0.0, -0.46, -0.42, 0.0, 0.0, -0.29, -0.25, 0.0, 0.0, 0.0, 0.0, -0.12, -0.1, 0.0, 0.0, -0.08);
                    kernels[15] = compute_kernel(x, -0.64, 0.49, 1.69, 1.41, 0.7, 0.68, -1.92, 0.94, 0.22, 1.52, 1.16, -7.59, 4.09, 2.91, 1.38, 3.54, -1.65, -2.99, 0.64, -1.37, 8.02, -9.24, -0.81, 1.69, -17.54, 8.16, 3.73, 4.77, 1.94, 1.97, -4.97, -2.0, 0.0, -1.99, 0.99, -0.97, 0.0, 0.0, -0.91, -0.88, 0.0, 0.0, 0.0, 0.0, -0.69, -0.64, -0.6, -0.55, -0.51, 0.0, -0.42, 0.0, -0.33, 0.0, 0.0, -0.22, -0.19, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.08);
                    kernels[16] = compute_kernel(x, -1.28, -0.74, -0.89, -1.1, -0.46, 0.41, -0.8, 0.0, -0.88, 3.29, 0.58, -2.97, 0.37, 2.08, -6.9, -5.06, -1.65, -3.58, -1.28, 0.0, -1.46, 0.0, 0.81, -0.84, 0.0, -0.91, 0.0, 0.0, -0.97, 0.0, -0.99, -1.0, -1.0, 0.0, 0.0, -0.97, -0.95, -0.93, -0.91, 0.0, -0.84, -0.81, 0.0, 0.0, -0.69, 0.0, -0.6, 0.0, -0.51, -0.46, -0.42, 0.0, -0.33, -0.29, -0.25, 0.0, -0.19, 0.0, -0.14, -0.12, 0.0, 0.0, -0.08, 0.0);
                    kernels[17] = compute_kernel(x, -0.56, 0.33, -1.52, 0.2, 1.05, 1.9, 2.72, 0.38, -1.09, -1.77, 0.58, -3.63, 0.37, -5.4, 2.3, 5.06, 2.76, 2.39, -3.85, -2.06, 1.46, -2.31, 8.89, -5.07, 1.75, 3.63, -14.92, -1.91, -0.97, 3.94, 1.99, -2.0, -5.0, -0.99, 0.99, -0.97, -0.95, -0.93, -0.91, -0.88, -0.84, -0.81, -0.77, -0.73, -0.69, -0.64, -0.6, 0.55, -0.51, 0.0, 0.0, -0.37, 0.0, 0.0, -0.25, -0.22, -0.19, 0.0, 0.0, -0.12, -0.1, 0.0, 0.0, -0.08);
                    kernels[18] = compute_kernel(x, -0.24, 0.82, 1.69, 0.4, -0.23, 0.54, -0.48, 0.75, -0.22, -1.77, -4.65, 0.66, -0.37, -7.48, 0.0, -1.01, -2.76, 1.19, 0.0, -0.69, 2.19, -0.77, -1.62, 0.0, 0.0, 0.0, -0.93, 0.0, 0.0, -0.99, 0.0, 0.0, 0.0, -0.99, -0.99, 0.0, 0.0, -0.93, 0.0, -0.88, 0.0, -0.81, 0.0, -0.73, -0.69, 0.0, 0.0, 0.0, -0.51, -0.46, -0.42, -0.37, -0.33, 0.0, 0.0, -0.22, -0.19, -0.16, 0.0, 0.0, 0.0, 0.0, -0.08, -0.08);
                    kernels[19] = compute_kernel(x, -0.56, 0.58, -0.27, 0.7, -0.81, -1.5, 2.24, -3.19, 1.09, 2.53, -1.74, -0.33, 3.35, -1.66, 0.46, -4.04, 6.07, -3.58, -1.28, 6.87, -13.85, -10.01, -6.47, -3.38, -0.88, 0.0, 0.93, 0.95, 0.0, -0.99, -0.99, -1.0, 0.0, -0.99, -0.99, 0.0, -0.95, 0.0, -0.91, 0.0, 0.0, 0.81, -0.77, 0.0, -0.69, -0.64, -0.6, 0.0, -0.51, 0.0, -0.42, 0.0, 0.0, 0.0, -0.25, 0.0, 0.0, -0.16, 0.0, 0.0, -0.1, -0.09, 0.0, 0.0);
                    kernels[20] = compute_kernel(x, -1.12, 1.4, 0.36, -0.7, 0.0, -1.63, -1.44, -0.56, 0.22, -0.25, 0.0, 0.0, -0.37, 0.0, 0.0, 0.0, -0.55, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.88, -0.91, 0.0, -0.95, 0.0, 0.0, 0.0, 0.0, 0.0, -0.99, -0.99, -0.97, -0.95, 0.0, -0.91, -0.88, 0.0, -0.81, 0.0, 0.0, -0.69, -0.64, 0.0, -0.55, -0.51, -0.46, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.14, 0.0, 0.0, -0.09, -0.08, 0.0);
                    kernels[21] = compute_kernel(x, -1.12, 0.33, -0.18, -1.71, 0.35, -0.14, -0.32, 0.38, 0.0, -0.51, 0.87, -0.66, -0.37, -0.42, -0.46, -0.51, -0.55, 0.0, -0.64, 0.0, -0.73, -0.77, 0.0, 0.0, 0.0, -0.91, 0.0, -0.95, 0.0, -0.99, 0.0, 0.0, 0.0, 0.0, 0.0, -0.97, 0.0, 0.0, -0.91, 0.0, -0.84, -0.81, -0.77, 0.0, -0.69, -0.64, 0.0, -0.55, -0.51, -0.46, 0.0, -0.37, 0.0, 0.0, -0.25, 0.0, 0.0, 0.0, -0.14, -0.12, 0.0, -0.09, -0.08, 0.0);
                    kernels[22] = compute_kernel(x, -0.24, -0.25, 0.45, 0.4, -0.46, -0.68, -0.16, 0.19, -0.22, -0.25, -0.29, -0.33, 0.0, -0.42, -0.46, 0.0, 0.0, -0.6, 0.0, -0.69, 0.73, -0.77, 0.0, 0.0, -0.88, 0.0, 0.0, -0.95, -0.97, -0.99, -0.99, 0.0, -1.0, 0.0, -0.99, -0.97, 0.0, 0.0, 0.0, 0.0, -0.84, -0.81, 0.0, 0.0, -0.69, -0.64, 0.0, 0.0, 0.0, -0.46, -0.42, -0.37, 0.0, 0.0, 0.0, -0.22, -0.19, -0.16, -0.14, -0.12, 0.0, -0.09, -0.08, 0.0);
                    float decision = -0.755013306618;
                    decision = decision - (+kernels[0] * -0.028130982901 + kernels[1] * -0.009116085313 + kernels[2] * -0.045883905241 + kernels[3] * -0.048744377976 + kernels[4] * -0.04224162147 + kernels[5] * -0.215022583769 + kernels[6] * -0.136425422008 + kernels[7] * -0.010994109857 + kernels[8] * -0.004717329376 + kernels[9] * -0.104685978184 + kernels[10] * -0.050223231227);
                    decision = decision - (+kernels[11] * 0.005120268966 + kernels[12] * 0.025900177974 + kernels[13] * 0.002960613823 + kernels[14] * 0.01297469472 + kernels[15] * 0.004409291011 + kernels[16] * 0.015506210809 + kernels[17] * 0.008830971843 + kernels[18] * 0.04781439601 + kernels[19] * 0.013834622557 + kernels[20] * 0.124839202453 + kernels[21] * 0.151194370972 + kernels[22] * 0.282800806184);

                    return decision > 0 ? 0 : 1;
                }

                /**
                 * Convert class idx to readable name
                 */
                String predictLabel(float *x) const
                {
                    switch (predict(x))
                    {
                    case 0:
                        return String("pause");
                    case 1:
                        return String("start");
                    default:
                        return String("unknown");
                    }
                }

            protected:
                /**
                 * Compute kernel between feature vector and support vector.
                 * Kernel type: linear
                 */
                float compute_kernel(float *x, ...) const
                {
                    va_list w;
                    va_start(w, 64);
                    float kernel = 0.0;

                    for (uint16_t i = 0; i < 64; i++)
                    {
                        kernel += x[i] * va_arg(w, double);
                    }

                    return kernel;
                }
            };
        } // namespace Port
    }     // namespace ML
} // namespace Eloquent