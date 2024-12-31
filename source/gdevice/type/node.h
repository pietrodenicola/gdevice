#pragma once


#include "type/gpu.h"
#include "type/array.h"

#include "__temp/texture.h"
#include "gpu/program.h"
#include "__temp/light.h"
//#include "material.h"
#include "__temp/vertexbuffer.h"
#include "gpu/indexbuffer.h"

// PROP
//
//  VAO, it's a context for restoring every binding pertaining a object. Just bind the VAO and draw elements.
//  http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=258926
//
//	int				vao;
//	Buffer<Vertex>*	vbo;	// refers to a vbo of a geometry table.
//	Buffer<uint8>*	ibo;	// refers to a ibo of a connectivity table (NB: vbo.size will tell whether uint8 or uint16).
//	Array<ivec2>*	lod;	// comes together with the ibo, it selects a part of ibo (maybe 1 lod only) or a range.
//
//	NB: if vbo!=NULL && ibo==NULL then generate_ibo_lod(vbo, ibo, lod)
//  

// On VBO binding:
// - cache it if not cached yet
// - bind the attribute pointers
// - bind the 'detail' attribute as an input texture

struct Node;
struct Child;

struct Parent 
{
	Array<Node*> children; // TODO use Child* instead of Node*
};

struct Child 
{
// TODO Parent* parent;
    Node* parent; // TODO use Parent* instead of Node*
};
/*
struct Hierarchy 
{
    Node* parent;
	Array<Node*> children;
};
*/
struct Transform 
{
    mat3 transform;
};

struct Culling
{
    vec4 AABB;
};

struct Geometry 
{
	//Material*		material; // TerrainMaterial by default
	VertexBuffer*	vbo;
	IndexBuffer*	ibo;
};

struct Impostor 
{
    vec2			impostorDirection;
	float			impostorDistance;
	Texture<rgba>	impostorTexture;	
};

struct TileData
{
    vec4 tileID;
};




struct Node : Cacheable, Parent, Child, Transform, TileData, Geometry, Culling, Impostor
{
	//vec4 tileID;		// NOTE Tile only // (x,y,size, reserved) // size>0 means it's a terrain tile
	///////////////////////////////////////////////

	//mat3 transform;
	//vec4 bound;								// (center,radius) for sphere/frustum culling

	// impostering
	//vec2			impostor_direction;		// vec3 impostor_id
	//float			impostor_distance;
	//Texture<rgba>	impostor;				//rgb+height

	// PROP no more light nodes in scene 
	// TODO change to radiosity/AAOC info
	//Light*			light;	

	// normal rendering
	//Material*		material;
	//VertexBuffer*	vbo;
	//IndexBuffer*	ibo;				// pointer, because 1 vertex buffer can have more ways to be connected

    // TODO: Node* coarser;
    // TODO: vec2 coarserQuadrant;

    //Node* parent;
	//Array<Node*> children;

	Node()
	{
		transform.position	= vec3(0);
		transform.rotation	= vec3(0);
		transform.scale		= vec3(1);

		//this->material	= NULL;
		//this->light		= NULL;	
		this->vbo		= NULL;
		this->ibo		= NULL;
		this->parent	= NULL;
	}

};