#include "ServiceGenerator/ImportState.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/RootState.h"
#include "ServiceGenerator/common_definition.h"
#include "ServiceGenerator/ImportParseEndState.h"
#include "ServiceGenerator/ImportPathParseState.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"
#include "ServiceGenerator/ImportPathParseEndState.h"
#include "ServiceGenerator/ImportPathParseBeginState.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ImportState::ImportState(StateMachineState* const parent_state, StateMachine* sm) : ServiceGeneratorStateMachineState(IMPORT_STATE_NAME, parent_state, sm)
{
    this->AddSubState(new ImportPathParseBeginState(this, sm_))->AddSubState(new ImportPathParseState(this, sm_))->AddSubState(new ImportPathParseEndState(this, sm_))->AddSubState(new ImportParseEndState(this, sm_));
}

ImportState::~ImportState()
{
}

void ImportState::Init()
{
    this->SetDefaultSubState(sm_->GetStatePtr(IMPORT_PATH_PARSE_BEGIN_STATE_NAME));
    this->RegisterTransitionEventCallback(IMPORT_PATH_PARSE_COMPLETE_EVENT_NAME, static_cast<size_t>(StateEventPriority::LevelTwoPriority), TRANSITION_TRUE_CONDITION, sm_->GetStatePtr(IMPORT_PATH_PARSE_END_STATE_NAME), std::bind(&ImportState::ParseImportFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool ImportState::ParseImportFile(StateMachineState* src, StateMachineState* tgt, StateMachineEvent evt)
{
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("----------------------------------parse import file----------------------------------\n");
    ImportPathParseState* import_path_parse_state = dynamic_cast<ImportPathParseState*>(sm_->GetStatePtr(IMPORT_PATH_PARSE_STATE_NAME));
    ServiceGeneratorMachine* sm = static_cast<ServiceGeneratorMachine*>(sm_);
    if (sm == nullptr) {
        return false;
    }
    if (sm->IsImportAlready(import_path_parse_state->GetPath())) {
        return true;
    }
    ServiceGeneratorMachine* sub_sm = new ServiceGeneratorMachine(false);
    RootState* sub_root_state = new RootState(sub_sm);
    printf("?????????\n");
    std::string sub_service_file = import_path_parse_state->GetPath()[0] == '/' ? import_path_parse_state->GetPath() : (sm->GetServiceFilePath() + "/" + import_path_parse_state->GetPath());
    sub_sm->RegisterState(sub_root_state);
    sub_root_state->InitAll();
    sub_sm->ActiveRootState();
    printf("Import Proto File Output Path : %s\n", sm->GetProtoFileOutputPath().c_str());
    printf("Import CXX File Output Path : %s\n", sm->GetCXXFileOutputPath().c_str());
    printf("Import File : %s\n", sub_service_file.c_str());

    sub_sm->SetProtoFileOutputPath(sm->GetProtoFileOutputPath())->SetCXXFileOutputPath(sm->GetCXXFileOutputPath());
    sub_sm->ParseRpcServiceFile(sub_service_file);
    auto keywords = sub_sm->GetCustomKeyWords();
    auto direct_import_keywords = sub_sm->GetDirectImportCustomKeyWords();
    auto indirect_import_keywords = sub_sm->GetIndirectImportCustomKeyWords();
    auto pkg_set = sub_sm->GetPackageSet();
    std::unordered_set<std::string> sub_custom_keywords;
    for (auto set_it = direct_import_keywords.begin(); set_it != direct_import_keywords.end(); set_it++) {
        if (sm->GetServiceFile() == set_it->first) {
            // 循环引用
            throw std::exception();
        }
        if (sm->IsImportAlready(set_it->first)) {
            continue;
        }
        sm->AddIndirectImportCustomKeyWord(set_it->first, set_it->second);
        for (auto keyword_it = set_it->second.begin(); keyword_it != set_it->second.end(); keyword_it++) {
            if (sm->IsCustomKeyWord(*keyword_it)) {
                printf("1111111111111133333333333333331\n");
                throw std::exception();
            }
            sm->AddCustomKeyWord(*keyword_it, false);
        }
    }
    for (auto set_it = indirect_import_keywords.begin(); set_it != indirect_import_keywords.end(); set_it++) {
        if (sm->GetServiceFile() == set_it->first) {
            // 循环引用
            throw std::exception();
        }
        if (sm->IsImportAlready(set_it->first)) {
            continue;
        }
        sm->AddIndirectImportCustomKeyWord(set_it->first, set_it->second);
        for (auto keyword_it = set_it->second.begin(); keyword_it != set_it->second.end(); keyword_it++) {
            if (sm->IsCustomKeyWord(*keyword_it)) {
                printf("111111111111111\n");
                throw std::exception();
            }
            sm->AddCustomKeyWord(*keyword_it, false);
        }
    }
    for (auto it = keywords.begin(); it != keywords.end(); it++) {
        if (it->second) {
            if (sm->IsCustomKeyWord(it->first)) {
                printf("1111111111111112222222222222\n");
                throw std::exception();
            }
            sub_custom_keywords.insert(it->first);
            sm->AddCustomKeyWord(it->first, false);
        }
    }
    sm->AddDirectImportCustomKeyWord(import_path_parse_state->GetPath(), sub_custom_keywords);
    for (auto pkg_it = pkg_set.begin(); pkg_it != pkg_set.end(); pkg_it++) {
        sm->AddImportPackage(*pkg_it);
    }

    delete sub_sm;
    delete sub_root_state;
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("----------------------------------parse import file----------------------------------\n");

    return true;
}

StateMachineState* ImportState::onEnter()
{
    ImportPathParseState* import_path_parse_state = dynamic_cast<ImportPathParseState*>(sm_->GetStatePtr(IMPORT_PATH_PARSE_STATE_NAME));
    if (import_path_parse_state == nullptr) {
        throw std::exception();
    }
    import_path_parse_state->ResetPath();

    return this;
}

StateMachineState* ImportState::onExit()
{
    return this;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
