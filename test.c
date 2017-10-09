#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

int main() {
  cl_int status = CL_SUCCESS;

  // Get platform count
  cl_uint nb_platforms = 0;
  status = clGetPlatformIDs(0, NULL, &nb_platforms);
  if (status != CL_SUCCESS) {
    printf("clGetPlatformIDs[0] error: %d\n", status);
    return 1;
  }
  if (nb_platforms == 0) {
    printf("No OpenCL platform found.\n");
    return 0;
  } else {
    printf("%d OpenCL platform(s):\n", nb_platforms);
  }

  // Alloc and get platforms
  cl_platform_id* platforms = NULL;
  platforms = (cl_platform_id*)malloc(nb_platforms * sizeof(cl_platform_id));
  if (platforms == NULL) {
    printf("Unable to alloc '%s'\n", "platforms");
    return 1;
  }
  status = clGetPlatformIDs(nb_platforms, platforms, NULL);
  if (status != CL_SUCCESS) {
    printf("clGetPlatformIDs[1] error: %d\n", status);
    return 1;
  }

  // Loop over platforms to get devices
  for (unsigned int ip = 0; ip < nb_platforms; ++ip) {
    printf("Platform %d:\n", ip);

    // Get device count
    cl_uint nb_devices = 0;
    status = clGetDeviceIDs(
        platforms[ip], CL_DEVICE_TYPE_ALL, 0, NULL, &nb_devices);
    if (status != CL_SUCCESS) {
      printf("clGetDeviceIDs[0] error: %d\n", status);
      return 1;
    }
    if (nb_devices == 0) {
      printf("  No OpenCL device found.\n");
      continue;
    } else {
      printf("  %d OpenCL device(s):\n", nb_devices);
    }

    // Alloc and get devices
    cl_device_id* devices = NULL;
    devices = (cl_device_id*)malloc(nb_devices * sizeof(cl_device_id));
    if (devices == NULL) {
      printf("Unable to alloc '%s'\n", "devices");
      return 1;
    }
    status = clGetDeviceIDs(
        platforms[ip], CL_DEVICE_TYPE_ALL, nb_devices, devices, 0);
    if (status != CL_SUCCESS) {
      printf("clGetDeviceIDs[1] error: %d\n", status);
      return 1;
    }

    // Create context
    cl_context context = clCreateContext(
        NULL, 1, devices, NULL, NULL, &status);
    if (status != CL_SUCCESS) {
      printf("clCreateContext error: %d\n", status);
      return 1;
    }





    // Release context
    status = clReleaseContext(context);
    if (status != CL_SUCCESS) {
      printf("clReleaseContext error: %d\n", status);
      return 1;
    }

    // Release devices
    free(devices);
    devices = NULL;
  }

  // Release platforms
  free(platforms);
  platforms = NULL;

  return 0;
}
