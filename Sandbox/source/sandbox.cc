#include <iostream>

#include "entrypoint.hh"

#include "sandbox.hh"

void sandbox::run()
{
  while(true);
}

Bandolier::AppPtr Bandolier::CreateApplication()
{
  return std::make_unique<sandbox>();
}

