#include "GUI.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

using namespace math;

GUI::GUI(Window& window)
{
}

void GUI::shaderPreview(ShaderProgram s, MeshObject &obj)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    auto& mat = obj.materials[0];
    static float gamma = s.getGamma();
    float &metalness = mat.metallic;
    float &roughness = mat.roughness;
    Vector3 &color = mat.basecolor;

    ImGui::Begin("Shader preview");

    ImGui::SliderFloat("Gamma", &gamma, 0.0f, 5.0f);
    ImGui::ColorEdit3("Base color", (float*)&color);

    ImGui::SliderFloat("Metalness", &metalness, 0.0f, 1.0f);
    ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    s.setCurrentMaterial(mat);
    s.setGamma(gamma);
}
