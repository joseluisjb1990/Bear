#include <iostream>
#include <cstdlib>

#include "mc_driver.hpp"

int
main(const int argc, const char **argv)
{
   if(argc != 2 )
      return ( EXIT_FAILURE );
   MC::MC_Driver driver;

   driver.parse( argv[1] );

   return( EXIT_SUCCESS );
}
