#ifndef GO_MANAGER
#define GO_MANAGER

#include <vector>
#include "gameObject.hpp"

class goManager
{
    public:

        std::vector<std::unique_ptr<gameObject>> go_vector;

    protected:

    private:
};

#endif //GO_MANAGER
