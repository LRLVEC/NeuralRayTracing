#pragma once
#define _CUDA
#include <_NBody.h>
#include <CUDA/_CUDA_NBody_Device.cuh>
#include <_Math.h>
#include <_Time.h>

namespace NRT
{
	struct CudaRenderBuffer
	{

	};
	// nerf, sdf, mesh renderer base
	struct RendererBase: OpenGL::OpenGL
	{
		
	};
}


