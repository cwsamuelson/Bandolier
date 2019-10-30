#include <Renderer/render_command.hh>
#include <imgui.h>
#include <Renderer/renderer.hh>
#include <platform/OpenGL/open_gl_shader.hh>
#include <platform/OpenGL/open_gl_texture_2_d.hh>
#include "example_layer.hh"
#include "../../Bandolier/vendor/glm/glm/ext.hpp"

Example::Example()
        : Layer("Example")
          , mVAO(Bandolier::VertexArray::Create())
          , mCamera(-1.6f, 1.6f, -0.9f, 0.9f)//! @TODO don't do it this way..?
{
  std::vector<float> vertices{
          -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
          0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
  };
  std::vector<unsigned int> indices{
          0, 1, 2,
  };

  auto VBO = Bandolier::VertexBuffer::create(vertices);
  auto IBO = Bandolier::IndexBuffer::create(indices);

  VBO->Layout() = Bandolier::BufferLayout {
          {Bandolier::ShaderDataType::Float3, "a_Position"},
          {Bandolier::ShaderDataType::Float4, "a_Color"},
  };

  mVAO->AddVertexBuffer(VBO);
  mVAO->SetIndexBuffer(IBO);

  std::vector<float> squareVertices{
          -0.5f, -0.5f, 0.0f,
           0.5f, -0.5f, 0.0f,
           0.5f,  0.5f, 0.0f,
          -0.5f,  0.5f, 0.0f,
  };
  std::vector<uint32_t> squareIndices{
          0, 1, 2, 2, 3, 0
  };

  std::vector<float> texSquareVertices{
          -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
           0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
           0.5f,  0.5f, 0.0f, 1.0, 1.0f,
          -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
  };
  std::vector<uint32_t> texSuareIndices{
          0, 1, 2, 2, 3, 0
  };

  mSquareVAO = Bandolier::VertexArray::Create();
  auto squareVB = Bandolier::VertexBuffer::create(squareVertices);
  auto squareIB = Bandolier::IndexBuffer::create(squareIndices);
  squareVB->Layout() = Bandolier::BufferLayout{
          {Bandolier::ShaderDataType::Float3, "a_Position"},
  };
  mSquareVAO->AddVertexBuffer(squareVB);
  mSquareVAO->SetIndexBuffer(squareIB);

  mTexVAO = Bandolier::VertexArray::Create();
  auto texVB = Bandolier::VertexBuffer::create(texSquareVertices);
  auto texIB = Bandolier::IndexBuffer::create(texSuareIndices);
  texVB->Layout() = Bandolier::BufferLayout{
          {Bandolier::ShaderDataType::Float3, "a_Position"},
          {Bandolier::ShaderDataType::Float2, "a_TexCoord"},
  };
  mTexVAO->AddVertexBuffer(texVB);
  mTexVAO->SetIndexBuffer(texIB);

  mTexture = Bandolier::Texture2D::Create("assets/textures/Checkerboard.png");
  mAlphaTex = Bandolier::Texture2D::Create("assets/textures/Alpha.png");

  mShader        = Bandolier::Shader::Create("assets/shaders/MagicColor.glsl");
  mColorShader   = Bandolier::Shader::Create("assets/shaders/FlatColor.glsl");
  mTextureShader = Bandolier::Shader::Create("assets/shaders/Texture.glsl");

  std::dynamic_pointer_cast<Bandolier::OpenGlShader>(mTextureShader)->Bind();
  std::dynamic_pointer_cast<Bandolier::OpenGlShader>(mTextureShader)->SetUniform("u_Texture", 0);
}

Example::~Example()
{}

void
Example::OnAttach()
{
  Bandolier::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

  mCamera.SetPosition({ 0.5f, 0.5f, 0.0f });
  mCamera.SetRotation(45.0f);
}

void
Example::OnDetach()
{}

void
Example::RenderImGui()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
  ImGui::End();
}

void
Example::RenderOpenGL()
{
  Bandolier::Renderer::BeginScene(mCamera);

  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

  auto oglShader = std::dynamic_pointer_cast<Bandolier::OpenGlShader>(mColorShader);
  oglShader->Bind();
  oglShader->SetUniform("u_Color", mSquareColor);
  for(int y = 0; y < 20; ++y)
  {
    for(int x = 0; x < 20; ++x)
    {
      glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

      Bandolier::Renderer::Submit(mColorShader, mSquareVAO, transform);
    }
  }

  mTexture->Bind(0);
  Bandolier::Renderer::Submit(mTextureShader, mTexVAO);
  mAlphaTex->Bind(0);
  Bandolier::Renderer::Submit(mTextureShader, mTexVAO);

  Bandolier::Renderer::Submit(mShader, mVAO);

  Bandolier::Renderer::EndScene();
}

void
Example::OnUpdate(Bandolier::time_step)
{
  RenderImGui();

  RenderOpenGL();
}

bool
Example::OnEvent(const Bandolier::Events::BaseEvent& e)
{
  return false;
}

