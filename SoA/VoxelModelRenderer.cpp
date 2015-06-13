#include "stdafx.h"
#include "VoxelModelRenderer.h"
#include "ShaderLoader.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "VoxelMatrix.h"
#include "VoxelModel.h"
#include "VoxelModelMesh.h"

void VoxelModelRenderer::initGL() {
    m_program = ShaderLoader::createProgramFromFile("Shaders/Models/VoxelModel.vert",
                                                    "Shaders/Models/VoxelModel.frag");
}

void VoxelModelRenderer::draw(VoxelModel* model, f32m4 mVP, f32v3 translation, f32v3 eulerRotation, f32v3 scale) {
    f32m4 mW = f32m4(1.0f);
    f32m4 mWVP = mVP * mW;

    m_program.use();
    glUniformMatrix4fv(m_program.getUniform("unWVP"), 1, false, &mWVP[0][0]);
    glUniformMatrix4fv(m_program.getUniform("unW"), 1, false, &mW[0][0]);
    // TODO(Ben): Temporary
    glUniform3f(m_program.getUniform("unLightDirWorld"), 1.0f, 0.0f, 0.0f);

    model->getMesh().bind();
    m_program.enableVertexAttribArrays();
    glVertexAttribPointer(m_program.getAttribute("vPosition"), 3, GL_FLOAT, false, sizeof(VoxelModelVertex), offsetptr(VoxelModelVertex, pos));
    glVertexAttribPointer(m_program.getAttribute("vColor"), 3, GL_UNSIGNED_BYTE, true, sizeof(VoxelModelVertex), offsetptr(VoxelModelVertex, color));
    glVertexAttribPointer(m_program.getAttribute("vNormal"), 3, GL_FLOAT, false, sizeof(VoxelModelVertex), offsetptr(VoxelModelVertex, normal));

    glDrawElements(GL_TRIANGLES, model->getMesh().getIndexCount(), GL_UNSIGNED_INT, nullptr);
    model->getMesh().unbind();

    vg::GLProgram::unuse();
}