#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/RootState.h"

using namespace Imagine_Rpc::ServiceGenerator;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        printf("please input two parameter at least!\n");

        return 0;
    }
    std::string file_name = argv[1];
    ServiceGeneratorMachine* sm = new ServiceGeneratorMachine(file_name);
    RootState* root_state = new RootState(sm);
    sm->RegisterState(root_state);
    root_state->InitAll();
    sm->ActiveRootState();
    sm->ParseRpcServiceFile();

    delete sm;
    delete root_state;

    return 0;
}