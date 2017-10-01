#include <iostream>
#include "NetworkManager.hpp"
#include "babelClientManager.hpp"

babel::NetworkManager::NetworkManager(babel::BabelClientManager& ancestor)
:
    _root(ancestor),
    _networkTcp(std::make_shared<babel::QNetworkTcpClient>(*this)),
    _networkUdp(std::make_shared<babel::QNetworkUdp>(*this)),
    _cmds({
        {42, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS (" << t.code << ")" << std::endl;
        }},
        { 43, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS JOIN (" << t.code << ")" << std::endl;
            babel::t_clientCallJoinList list = *(reinterpret_cast<babel::t_clientCallJoinList*>(t.data.data()));

            this->_root.getCall().getCurrentCall().setIdConv(list.idConv);

            std::cout << "--------- SUCCESS JOIN IDCONV: " << list.idConv << std::endl;

            if (this->_root.getCall().isOwner())
                this->_root.getUI().inviteContactInConversation();
        } },
        { 44, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS LOGIN (" << t.code << ")" << std::endl;
            this->_root.getUI().hideWindow("LoginDiag");
            this->_root.getUI().refreshGeneralInformations();
            this->_root.getUI().showWindow("MainWindow");
        } },
        { 45, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS SIGNUP(" << t.code << ")" << std::endl;
            this->_root.getUI().hideWindow("SignupDiag");
            this->_root.getUI().refreshGeneralInformations();
            this->_root.getUI().showWindow("MainWindow");
        } },
        { 46, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS DEL (" << t.code << ")" << std::endl;
        } },
        { 47, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS ADD (" << t.code << ")" << std::endl;
        } },
        { 48, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS INVITE (" << t.code << ")" << std::endl;

        } },
        { 49, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS LEAVE (" << t.code << ")" << std::endl;
        } },
        { 501, [&](babel::t_babelPackedData t) {
            std::cout << "INTERNAL ERROR(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("Internal error");
        } },
        { 502, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS LOGIN USED(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("Login already in use >.<");
        } },
        { 503, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS WRONG CREDENTIALS(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("Wrong credentials :/");
        } },
        { 505, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS NO SUCH USER(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("User not found :(");
        } },
        { 506, [&](babel::t_babelPackedData t) {
            std::cout << "SUCCESS NO SUCH CONV(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("This conv does not exist :(");
        } },
        { 6, [&](babel::t_babelPackedData t) {
            std::cout << "CONTACT LIST(" << t.code << ")" << std::endl;
            babel::t_clientContactList list = *(reinterpret_cast<babel::t_clientContactList*>(t.data.data()));
            std::vector<babel::Contact> listContact;
            int i = 0;
            for (; i < 50; i++) {
                if (!*(list.contacts[i].login))
                    break;
                listContact.push_back(babel::Contact(list.contacts[i].login, list.contacts[i].isOnline));
                std::cout << i + 1 << ". " << list.contacts[i].login << std::endl;
            }
            this->_root.getContact().updateContactList(listContact);
            this->_root.getUI().updateFriendsListFromContactManager();
        } },
        { 7, [&](babel::t_babelPackedData t) {
            std::cout << "INVITE CALL(" << t.code << ")" << std::endl;

            babel::t_clientCallInviteList list = *(reinterpret_cast<babel::t_clientCallInviteList*>(t.data.data()));
            std::vector<std::string>    listContactStr;

            std::cout << "---- > Begin reading data !" << std::endl;
            std::cout << "---- > Owner: " << list.owner << std::endl;
            this->_root.getUI().clearConversationList();
            for (int i = 0; i < 8; i++) {
                if (!*(list.clients[i]))
                    break;
                std::cout << "------ > Reading client: " << list.clients[i] << std::endl;
                this->_root.getUI().appendToConversationList(list.clients[i]);
                listContactStr.push_back(list.clients[i]);
            }
            std::cout << "---- > End reading data !" << std::endl;
            if (listContactStr.size() == 1)
                this->_root.getUI().updateNameCallingText(listContactStr[0]);
            else if (listContactStr.size() > 1)
                this->_root.getUI().updateNameCallingText(listContactStr[0], std::vector<std::string>(listContactStr.begin() + 1, listContactStr.end()));
            this->_root.getCall().getCurrentCall().setIdConv(list.idConv);
            this->_root.getUI().refreshStatusWhenReceivingCall();
            this->_root.getUI().showWindow("ReceiveCallDiag");
        } },
        { 8, [&](babel::t_babelPackedData t) {
            std::cout << "LEAVE CALL(" << t.code << ")" << std::endl;
            this->_root.getUI().showErrorDialog("This conv does not exist :(");
        } },
        { 9, [&](babel::t_babelPackedData t) {
            std::cout << "JOIN CALL(" << t.code << ")" << std::endl;

            this->_root.getUI().showErrorDialog("This conv does not exist :(");
        } },
    })
{
    std::cout << "NetworkManager created" << std::endl;
    this->_networkTcp->connectToTcpHost(IP_MAIN_SERVER, SERVER_PORT);
}

babel::NetworkManager::~NetworkManager() {
    std::cout << "NetworkManager destructed" << std::endl;
}

babel::BabelClientManager& babel::NetworkManager::getRoot() const
{
    return this->_root;
}

const std::shared_ptr<babel::INetworkTcpClient> babel::NetworkManager::getNetworkTcp() const
{
    return this->_networkTcp;
}

std::shared_ptr<babel::INetworkTcpClient> babel::NetworkManager::getNetworkTcp()
{
    return this->_networkTcp;
}

void babel::NetworkManager::handleCmd(babel::t_babelPackedData& t)
{
    if (!this->_cmds[t.code])
        return;
    this->_cmds[t.code](t);
    std::cout << t.code << " - " << t.size << std::endl;
}

void babel::NetworkManager::writeServerTCP(babel::t_babelPackedData& t)
{
    this->_networkTcp->write(t);
}

void babel::NetworkManager::writeServerTCP(std::uint32_t code, std::uint32_t size, std::array<char, 2048> ba)
{
    babel::t_babelPackedData t;
    t.code = code;
    t.size = size;
    t.data = ba;
    this->_networkTcp->write(t);
}
