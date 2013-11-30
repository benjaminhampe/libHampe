// Copyright (C) 2008-2012 Benjamin Hampe
// This file uses parts of the "Irrlicht Engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_TEAPOT_SCENE_NODE_H__
#define __C_TEAPOT_SCENE_NODE_H__

#include <irrlicht.h>

namespace irr{
namespace scene{

//// 2 different teapot models
//// Model [0]: just triangles
//			const f32 teapot_v[1976][3] = {
//			const u16 teapot_i[3752][3] = {
//
//// Model [1]: not implemented

class CTeapotSceneNode : public ISceneNode
{
public:
	CTeapotSceneNode(
		ISceneNode* parent,
		ISceneManager* mgr,
		s32 id,
		f32 size = 100.0f,
		const core::vector3df& pos = core::vector3df(0,0,0),
		const core::vector3df& rot = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1,1,1));
public:
	virtual ~CTeapotSceneNode();

	virtual void OnRegisterSceneNode();

	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	virtual u32 getMaterialCount() const;

	virtual video::SMaterial& getMaterial(u32 i);

	virtual void render();

	static SMeshBuffer* createSimpleTeapotMeshBuffer( f32 size );

private:
	SMeshBuffer* Buffer;
};

} // END NAMSPACE SCENE
} // END NAMSPACE IRR
#endif
