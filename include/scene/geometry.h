// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_GEOMETRY_HELPER_H__
#define __IRR_EXT_GEOMETRY_HELPER_H__

#include <irrlicht.h>

#include "CAutoMeshSceneNode.h"

#include "../core/sinCosTable.h"

#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
	#include <functional>
#endif

namespace irr
{
namespace scene
{
namespace geometry
{
	///@brief create PolyLine from array of vector2d<T>

	template<class T>
	CAutoMeshSceneNode*
	createPolyLine(
		ISceneManager* smgr,
		ISceneNode* parent,
		const core::array<core::vector2d<T>>& points,
		const video::SColor& lineColor = video::SColor(255,0,0,0),
		const f32& lineWidth = 1.0f,
		const u16& lineStipple = 0xffff,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1,1,1) )
	{
		#ifdef _DEBUG
		printf("createPolyLine\n");
		#endif // _DEBUG

		u32 point_count = core::min_<u32>( points.size(), 65536 );
		if (point_count == 0)
			return 0; /// ERROR

		SMesh* mesh = new SMesh();
		if (!mesh)
			return 0; /// ERROR

		SMeshBuffer* p = new SMeshBuffer();
		if (!p)
			return 0; /// ERROR

		p->Material.Lighting = false;
		p->Material.Thickness = lineWidth;
		p->Material.AntiAliasing = 4;
		p->Material.FogEnable = false;
		p->Material.NormalizeNormals = false;

		p->Vertices.reallocate( point_count );
		p->Vertices.set_used( 0 );
		p->Indices.reallocate( point_count );
		p->Indices.set_used( 0 );

		for (u32 i=0; i<point_count; i++)
		{
			p->Vertices.push_back( video::S3DVertex( (f32)points[i].X, (f32)points[i].Y, 0.0f, 0.f, 0.f, -1.f, lineColor, 0.f, 0.f ) );
			p->Indices.push_back( i );
		}

		p->recalculateBoundingBox();

		mesh->addMeshBuffer( p );

		mesh->BoundingBox = p->getBoundingBox();

		p->drop();

		mesh->setHardwareMappingHint( EHM_STATIC);

		CAutoMeshSceneNode* node = new CAutoMeshSceneNode(
			mesh, smgr, parent, -1, EPT_LINE_STRIP, position, rotation, scale );

		mesh->drop();

		if (!node)
			return 0; /// ERROR

		node->setLineStipple( lineStipple );

		return node;
	}

	///@brief create AutoMeshSceneNode from PolyLine

	template<class T>
	CAutoMeshSceneNode*
	createPolyLine(
		ISceneManager* smgr,
		ISceneNode* parent,
#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
		const std::function<T (const T&)>& func,
#else
		const IFunctionOfTime* const func,
#endif
		const T& t_start,
		const T& t_end,
		const u32& point_count = 100,
		const video::SColor& lineColor = video::SColor(255,0,0,0),
		const f32& lineWidth = 1.0f,
		const u16& lineStipple = 0xffff,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1,1,1) )
	{
		typedef core::vector2d<f32> Vector2f;
		typedef core::array<Vector2f> ArrayOfVector2f;

		if (point_count == 0)
			return 0;

		ArrayOfVector2f points;
		points.reallocate( point_count );
		points.set_used( 0 );

		const T t_delta = (t_end - t_start) / (T)point_count;

		T t_now = t_start;

		#ifdef _DEBUG
		printf("point_count = %d, time_delta = %f\n", point_count, t_delta );
		#endif // _DEBUG

		for (u32 i=0; i<point_count; i++)
		{
			points.push_back( Vector2f( (f32)t_now, (f32)func(t_now) ) );
			t_now += t_delta;

			#ifdef _DEBUG
			printf("points[%d] = { %f, %f }\n", i, points[i].X, points[i].Y );
			#endif // _DEBUG
		}


		return createPolyLine<T>( smgr, parent, points, lineColor, lineWidth, lineStipple, position, rotation, scale );
	}




	IMesh* createTriangleMesh(
			const core::vector3df& A,
			const core::vector3df& B,
			const core::vector3df& C,
			const video::SColor& colorA,
			const video::SColor& colorB,
			const video::SColor& colorC);

	IMesh* createRectMesh(
			f32 width = 1.f,
			f32 height = 1.f,
			const video::SColor& bottomLeftColor = 0xffffffff,
			const video::SColor& topLeftColor = 0xffffffff,
			const video::SColor& topRightColor = 0xffffffff,
			const video::SColor& bottomRightColor = 0xffffffff);

	IMesh* createRoundRectMesh(
			f32 width = 1.0f,
			f32 height = 1.0f,
			f32 rx = .1f,
			f32 ry = .1f,
			u32 tesselation = 12,
			bool bFullyTextured = true,
			const video::SColor& outlineColor = 0xffffffff,
			const video::SColor& centerColor = 0xffffffff);

	IMesh* createHexagonMesh(
			const core::vector3df& size = core::vector3df(10,10,1),
			bool closeHull = false,
			bool closeBottom = false,
			const video::SColor& color = 0xffffffff);

	IMesh* createCircleMesh(
			f32 radius = 0.5f,
			u32 tesselation = 12,
			bool filled = true,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff);

	IMesh* createEllipseMesh(
			f32 radiusX = 0.5f,
			f32 radiusY = 0.4f,
			u32 tesselation = 12,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff);

	IMesh* createEllipsoidMesh(
			f32 radiusX = 0.5f,
			f32 radiusY = 0.3f,
			f32 radiusZ = 0.4f,
			u32 tessX = 12,
			u32 tessY = 12,
			u32 tessZ = 12,
			const video::SColor& color = 0xffffffff);

	IMesh* createRingMesh(
			f32 outerRadius = 0.5f,
			f32 innerRadius = 0.25f,
			u32 tesselation = 12,
			bool bRepeatTexture = false,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff);

	IMesh* createArcMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .25f,
			f32 angleStart = 0.0f,
			f32 angleEnd = 180.0f,
			u32 tesselation = 12,
			bool bRepeatTexture = true,
			const video::SColor& outerColor = 0xffffffff,
			const video::SColor& innerColor = 0xffffffff);

	IMesh* createCylinderMesh(
			f32 radius,
			f32 height,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bOneMaterial = false,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff);

	IMesh* createUpperSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeBottom = false);

	IMesh* createLowerSphereHalfMesh(
			f32 radius = .5f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			const video::SColor& color = 0xffffffff,
			bool closeTop = false);

	IMesh* createCapsuleMesh(
			f32 radius = .5f,
			f32 height = 1.0f,
			u32 tessCircle = 7,
			u32 tessRows = 7,
			u32 tessHull = 1,
			bool bOneMaterial = true,
			const video::SColor& color = 0xffffffff,
			const video::SColor& topColor = 0xffffffff,
			const video::SColor& bottomColor = 0xffffffff);

	IMesh* createTubeMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .4f,
			f32 height = 1.0f,
			u32 tessCircle = 12,
			u32 tessHull = 1,
			bool closeTop = true,
			bool closeBottom = true,
			bool bRepeatTextureCircle = false,
			bool bRepeatTextureHull = false,
			const video::SColor& color = 0xffffffff);

    IMesh* createBoxMesh(
			const core::vector3df& size,
	        const video::SColor& color = 0xffffffff,
	        u32 matCount = 6);

	IMesh* createTorusMesh(
			f32 outerRadius = .5f,
			f32 innerRadius = .1f,
			u32 tessOuterRadius = 12,
			u32 tessInnerRadius = 8,
			const video::SColor& color = 0xffffffff);

	IMesh* createLine2dMesh(
			const core::array<core::vector2df>& points,	// all containing points get connected by min. one quad
			const core::array<video::SColor>& colors, // color-array
			f32 thickness = 1.0f,
			s32 lineJoin = 0, // 0 == rect-miter, 1==rect-bevel, >2 == circle-round segments
			video::ITexture* pTexture = 0,
			bool bRepeatTexture=true); // false = each segments has full tex, if true, planar uv mapping on boundingrect

} // end namespace geometry

} // end namespace scene

} // end namespace irr

#endif // __IRR_EXT_GEOMETRY_HELPER_H__

