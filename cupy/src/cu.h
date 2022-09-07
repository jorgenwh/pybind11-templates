#include <cuda.h>
#include <cuda_runtime.h>

#define cuda_errchk(err) { cuda_errcheck(err, __FILE__, __LINE__); }
inline void cuda_errcheck(cudaError_t code, const char *file, int line, bool abort=true) {
  if (code != cudaSuccess) {
    fprintf(stderr, "CUDA assert: %s %s %d\n", cudaGetErrorString(code), file, line);
    if (abort) { exit(code); }
  }
}
