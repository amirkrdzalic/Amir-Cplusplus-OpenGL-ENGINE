#pragma once

#include "PrimitiveType.h"
#include "Camera3D.h"
#include "ShaderNova.h"
#include "SHAPEGL.h"

namespace Amir3DEngine
{
	class AbstractRenderer
	{

	public:
		AbstractRenderer() { }
		~AbstractRenderer() { }
		virtual void renderPrimitive(PrimitiveTypeDef type) = 0;
		virtual void renderPrimitive(SHAPEGL * shape, Camera3D * camera, ShaderNova * program) = 0;
	};
}

