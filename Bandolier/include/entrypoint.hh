#ifndef TEST_ENTRYPOINT_HH
#define TEST_ENTRYPOINT_HH

#include <memory>

#include <application.hh>

extern Bandolier::AppPtr Bandolier::CreateApplication();

int main(int argc, char* argv[])
{
  auto app = Bandolier::CreateApplication();
  app->run();
}

#endif //TEST_ENTRYPOINT_HH
