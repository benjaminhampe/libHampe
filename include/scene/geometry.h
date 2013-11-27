// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_EXT_GEOMETRY_CREATE_RECT_MESH_BUFFER_H__
#define __C_IRR_EXT_GEOMETRY_CREATE_RECT_MESH_BUFFER_H__

#include <irrlicht.h>

namespace irr
{

namespace scene
{
	///@brief Rect with 1 color(s)
	IMeshBuffer* createRectMB(
			f32 width = 1.0f,
			f32 height = 1.0f,
			const video::SColor& color = 0xffffffff,
			const f32 thickness = 0.0f /* filled == EPT_TRIANGLES*/ );

	///@brief Rect with 4 color(s)
	IMeshBuffer* createRectMB(
			f32 width = 1.f,
			f32 height = 1.f,
			const video::SColor& bottomLeftColor = 0xffffffff,
			const video::SColor& topLeftColor = 0xffffffff,
			const video::SColor& topRightColor = 0xffffffff,
			const video::SColor& bottomRightColor = 0xffffffff,
			const f32 thickness = 0.0f /* filled */ );

	///@brief RoundRect with 1 color(s)
	IMeshBuffer* createRoundRectMB(
			f32 width = 1.0f,
			f32 height = 1.0f,
			f32 rx = .1f,
			f32 ry = .1f,
			const video::SColor& color = 0xffffffff,
			const f32& thickness = 0.0f /* filled */,
			const u32& tesselation = 12);
			
} // end namespace scene

} // end namespace irr

#endif // __C_IRR_EXT_GEOMETRY_CREATE_RECT_MESH_BUFFER_H__

