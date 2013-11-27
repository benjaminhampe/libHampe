// Copyright (C) 2002-2013 Benjamin Hampe <BenjaminHampe@gmx.de>
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "geometry.h"

namespace irr
{

namespace scene
{

//! Create a Rectangular MeshBuffer with one color.
IMeshBuffer* createRectMeshBuffer(
	f32 width,
	f32 height,
	const video::SColor& color,
	f32 thickness,
	video::E_VERTEX_TYPE vType,
	E_PRIMITIVE_TYPE pType,
	u16 lineStipple,
	s32 lineFactor)
{
	IMeshBuffer* buffer = 0;

	switch (vType)
	{
		case video::EVT_STANDARD: buffer = new SMeshBuffer(); break;
		case video::EVT_2TCOORDS: buffer = new SMeshBufferLightMap(); break;
		case video::EVT_TANGENTS: buffer = new SMeshBufferTangents(); break;
		default: break;
	}

	if (!buffer)
		return 0;



	return buffer;
}


//! Create a Rectangular MeshBuffer with four colors.
IMeshBuffer* createRectMeshBuffer(
	f32 width,
	f32 height,
	const video::SColor& bottomLeftColor,
	const video::SColor& topLeftColor,
	const video::SColor& topRightColor,
	const video::SColor& bottomRightColor,
	f32 thickness,
	video::E_VERTEX_TYPE vType,
	E_PRIMITIVE_TYPE pType,
	u16 lineStipple,
	s32 lineFactor)
{
	IMeshBuffer* buffer = 0;

	switch (vType)
	{
		case video::EVT_STANDARD: buffer = new SMeshBuffer(); break;
		case video::EVT_2TCOORDS: buffer = new SMeshBufferLightMap(); break;
		case video::EVT_TANGENTS: buffer = new SMeshBufferTangents(); break;
		default: break;
	}

	if (!buffer)
		return 0;



	return buffer;
}

IMesh* createRectMesh(
		f32 width,
		f32 height,
		const video::SColor& bottomLeftColor,
		const video::SColor& topLeftColor,
		const video::SColor& topRightColor,
		const video::SColor& bottomRightColor)
{
	// triangle mesh
	SMesh* mesh = new SMesh();
	if (!mesh)
		return 0;

	// triangle meshbuffer
	SMeshBuffer* buffer = new SMeshBuffer();
	if (!buffer)
		return mesh;

	// material
	if (bottomLeftColor.getAlpha()<255 || topLeftColor.getAlpha()<255 ||
		topRightColor.getAlpha()<255 || bottomRightColor.getAlpha()<255)
		buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
	else
		buffer->Material.MaterialType = video::EMT_SOLID;

	// set buffer sizes
	buffer->Vertices.reallocate( 4 );
	buffer->Vertices.set_used( 0 );
	buffer->Indices.reallocate( 6 );
	buffer->Indices.set_used( 0 );

	// normale
	const core::vector3df n( 0,0,-1 );
	const f32 w = 0.5f*width;
	const f32 h = 0.5f*height;

	// add data to meshbuffer
	buffer->Vertices.push_back( video::S3DVertex( -w,-h,0,n.X,n.Y,n.Z,bottomLeftColor,0,1 ) );
	buffer->Vertices.push_back( video::S3DVertex( -w, h,0,n.X,n.Y,n.Z,topLeftColor,0,0 ) );
	buffer->Vertices.push_back( video::S3DVertex(  w, h,0,n.X,n.Y,n.Z,topRightColor,1,0 ) );
	buffer->Vertices.push_back( video::S3DVertex(  w,-h,0,n.X,n.Y,n.Z,bottomRightColor,1,1 ) );
	buffer->recalculateBoundingBox();

	buffer->Indices.push_back( 0 );
	buffer->Indices.push_back( 1 );
	buffer->Indices.push_back( 2 );
	buffer->Indices.push_back( 0 );
	buffer->Indices.push_back( 2 );
	buffer->Indices.push_back( 3 );

	// add meshbuffer to mesh
	mesh->addMeshBuffer( buffer );
	buffer->drop();

	// return mesh
	mesh->recalculateBoundingBox();
	mesh->setHardwareMappingHint(EHM_STATIC);
	return mesh;
}

} // end namespace scene

} // end namespace irr

