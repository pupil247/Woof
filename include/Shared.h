#pragma once

#include "singleton.hpp"



class Shared : public TSingleton<Shared>{

friend class TSingleton<Shared>;

private:
    Shared();
    ~Shared();

public:

   
};