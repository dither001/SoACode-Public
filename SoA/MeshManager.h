// 
//  MeshManager.h
//  Seed Of Andromeda
//
//  Created by Ben Arnold on 19 Oct 2014
//  Copyright 2014 Regrowth Studios
//  All Rights Reserved
//  
//  This file provides a mesh manager class, which handles
//  uploading various types of meshes to the GPU.
//

#pragma once

#ifndef MESHMANAGER_H_
#define MESHMANAGER_H_

#include <Vorb/VorbPreDecl.inl>

class ChunkMeshData;
class ParticleMeshMessage;
class PhysicsBlockMeshMessage;

class ChunkMesh;
class ParticleMesh;
class PhysicsBlockMesh;
class TerrainPatchMesh;


class MeshManager
{
public:
    MeshManager();

    /// Updates a particle mesh
    /// @param pmm: The ParticleMeshMessage sent by the update thread
    void updateParticleMesh(ParticleMeshMessage* pmm);

    /// Updates a physics block mesh
    /// @param pbmm: The PhysicsBlockMeshMessage sent by the update thread
    void updatePhysicsBlockMesh(PhysicsBlockMeshMessage* pbmm);

    /// Destroys all of the meshes and frees allocated memory
    void destroy();

    // Getters
    const std::vector <ParticleMesh*>& getParticleMeshes() const { return _particleMeshes; }
    const std::vector <PhysicsBlockMesh*>& getPhysicsBlockMeshes() const { return _physicsBlockMeshes; }

private:

    std::vector <ParticleMesh *> _particleMeshes;
    std::vector <PhysicsBlockMesh *> _physicsBlockMeshes;
};

#endif // MESHMANAGER_H_