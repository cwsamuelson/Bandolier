#ifndef TEST_ENTRYPOINT_HH
#define TEST_ENTRYPOINT_HH

#include <memory>

#include <Application.hh>
#include <logger.hh>

extern Bandolier::Application& Bandolier::CreateApplication();

int main(int argc, char* argv[])
{
  auto& app = Bandolier::CreateApplication();
  Bandolier::logging::core()->trace("APP INITIALIZED");
  Bandolier::logging::client()->trace("INITIALIZED");
  app.run();
}

#endif //TEST_ENTRYPOINT_HH
