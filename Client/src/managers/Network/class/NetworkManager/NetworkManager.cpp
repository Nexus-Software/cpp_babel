#include <iostream>
#include "NetworkManager.hpp"
#include "babelClientManager.hpp"

babel::NetworkManager::NetworkManager(babel::BabelClientManager& ancestor)
:
	_root(ancestor),
	_networkTcp(std::make_shared<babel::QNetworkTcpClient>(*this)),
	_networkUdp(std::make_shared<babel::QNetworkUdp>(*this)),
	_cmds({
		{42, [&](babel::t_babelPackedData t) {  this->C_Success(t);				}},
		{43, [&](babel::t_babelPackedData t) {  this->C_SuccessJoin(t);			}},
		{44, [&](babel::t_babelPackedData t) {  this->C_SuccessLogin(t);		}},
		{45, [&](babel::t_babelPackedData t) {	this->C_SuccessSignUp(t);		}},
		{46, [&](babel::t_babelPackedData t) {	this->C_SuccessDel(t);			}},
		{47, [&](babel::t_babelPackedData t) {	this->C_SuccessAdd(t);			}},
		{48, [&](babel::t_babelPackedData t) {	this->C_SuccessInvite(t);		}},
		{49, [&](babel::t_babelPackedData t) {	this->C_SuccessLeave(t);		}},
		{501, [&](babel::t_babelPackedData t) {	this->C_InternalError(t);		}},
		{502, [&](babel::t_babelPackedData t) {	this->C_ErrorAlreadyUsed(t);	}},
		{503, [&](babel::t_babelPackedData t) {	this->C_ErrorWrongCreds(t);		}},
		{505, [&](babel::t_babelPackedData t) {	this->C_ErrorUserNotFound(t);	}},
		{506, [&](babel::t_babelPackedData t) {	this->C_ConvNotFound(t);		}},
		{6, [&](babel::t_babelPackedData t) {	this->C_GetContactList(t);		}},
		{7, [&](babel::t_babelPackedData t) {	this->C_GetCallInvitation(t);	}},
		{8, [&](babel::t_babelPackedData t) {	this->C_NotifyLeaveCall(t);		}},
		{9, [&](babel::t_babelPackedData t) {	this->C_NotifyUserJoinConv(t);	}}
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

const std::shared_ptr<babel::INetworkUdp> babel::NetworkManager::getNetworkUdp(void) const
{
	return this->_networkUdp;
}

std::shared_ptr<babel::INetworkUdp> babel::NetworkManager::getNetworkUdp(void)
{
	return this->_networkUdp;
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

/* SERVER CALLBACK */


/////////////
//
// SUCCESS //
//
/////////////

void    babel::NetworkManager::C_Success(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS (" << t.code << ")" << std::endl;
}

void    babel::NetworkManager::C_SuccessJoin(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : JOIN (" << t.code << ")" << std::endl;

	babel::t_clientCallJoinList list = *(reinterpret_cast<babel::t_clientCallJoinList*>(t.data.data()));
	std::vector<t_clientCallStruct> listContact;

	this->_root.getCall().getCurrentCall().setIdConv(list.idConv);

	std::cout << "------------- IdConv = " << list.idConv << std::endl;
	int i = 0;
	for (; i < 50; i++) {
		if (!*(list.clients[i].login))
			break;
		listContact.push_back(list.clients[i]);
		std::cout << "------------- Client " << i + 1 << ". " << list.clients[i].login << " / " << list.clients[i].ip << " / " << list.clients[i].port << std::endl;
		if (std::string(list.clients[i].login) != this->_root.getContact().getUser().getLogin())
			this->getNetworkUdp()->clientWrite(std::string(list.clients[i].login), std::string(list.clients[i].ip), list.clients[i].port);
	}

	if (this->_root.getCall().isOwner()) {
		std::cout << "------------- I'm the owner, about to invite others to the calls" << std::endl;
		this->_root.getUI().inviteContactInConversation();
    } else {
        this->_root.getUI().clearConversationList();
        for (auto it : listContact)
            this->_root.getUI().appendToConversationList(it.login);
        this->_root.getUI().refreshWhenJoiningCall();
    }
 
}

void    babel::NetworkManager::C_SuccessLogin(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : LOGIN (" << t.code << ")" << std::endl;

	this->_root.getUI().hideWindow("LoginDiag");
	this->_root.getUI().refreshGeneralInformations();
	this->_root.getUI().showWindow("MainWindow");
}

void    babel::NetworkManager::C_SuccessSignUp(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : SIGNUP(" << t.code << ")" << std::endl;

	this->_root.getUI().hideWindow("SignupDiag");
	this->_root.getUI().refreshGeneralInformations();
	this->_root.getUI().showWindow("MainWindow");
}

void    babel::NetworkManager::C_SuccessDel(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : DEL (" << t.code << ")" << std::endl;
}

void    babel::NetworkManager::C_SuccessAdd(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : ADD (" << t.code << ")" << std::endl;
}

void    babel::NetworkManager::C_SuccessInvite(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : INVITE (" << t.code << ")" << std::endl;
    this->_root.getUI().refreshSelectedContact("Nobody yet.", babel::UIManager::ContactInfoType::IN_CALL);
}

void    babel::NetworkManager::C_SuccessLeave(babel::t_babelPackedData& t)
{
	std::cout << "SUCCESS : LEAVE (" << t.code << ")" << std::endl;
    this->_root.getUI().refreshWhenHangingUpCall();
}

////////////
//
// ERRORS //
//
////////////

void    babel::NetworkManager::C_InternalError(babel::t_babelPackedData& t)
{
	std::cout << "ERROR : INTERNAL ERROR (" << t.code << ")" << std::endl;
	this->_root.getUI().showDialog("MainWindow", "Internal Error", "Something unexpected gone wrong.", babel::UIManager::DialogType::CRITICAL);
}

void    babel::NetworkManager::C_ErrorAlreadyUsed(babel::t_babelPackedData& t)
{
	std::cout << "ERROR : LOGIN ALREADY USED (" << t.code << ")" << std::endl;
	this->_root.getUI().showDialog("SignupDiag", "Signup", "Login already in use >.<", babel::UIManager::DialogType::WARNING);
}

void    babel::NetworkManager::C_ErrorWrongCreds(babel::t_babelPackedData& t)
{
	std::cout << "ERROR : WRONG CREDENTIALS (" << t.code << ")" << std::endl;
	this->_root.getUI().showDialog("LoginDiag", "Login", "Wrong credentials :/", babel::UIManager::DialogType::WARNING);
}

void    babel::NetworkManager::C_ErrorUserNotFound(babel::t_babelPackedData& t)
{
	std::cout << "ERROR : USER NOT FOUND (" << t.code << ")" << std::endl;
	this->_root.getUI().showDialog("MainWindow", "User not found", "User not found :(", babel::UIManager::DialogType::CRITICAL);
}

void    babel::NetworkManager::C_ConvNotFound(babel::t_babelPackedData& t)
{
	std::cout << "ERROR : CONV NOT FOUND (" << t.code << ")" << std::endl;
	this->_root.getUI().showDialog("MainWindow", "Unknown conversation", "This conversation doesn't exist :(", babel::UIManager::DialogType::CRITICAL);
}

/////////////
//
// ACTIONS //
//
/////////////

void    babel::NetworkManager::C_GetContactList(babel::t_babelPackedData& t)
{
	std::cout << "ACTION : GET CONTACT LIST(" << t.code << ")" << std::endl;

	babel::t_clientContactList list = *(reinterpret_cast<babel::t_clientContactList*>(t.data.data()));

	/*std::cout << "----------- > DATA GET CONTACT LIST: ";
	for (int i = 0; i < 2048; ++i)
		std::cout << "[" << t.data.data()[i] << "]";
	std::cout << std::endl;*/

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
}

void    babel::NetworkManager::C_GetCallInvitation(babel::t_babelPackedData& t)
{
	std::cout << "ACTION : GET CALL INVITATION (" << t.code << ")" << std::endl;

	babel::t_clientCallInviteList list = *(reinterpret_cast<babel::t_clientCallInviteList*>(t.data.data()));
	std::vector<std::string>    listContactStr;

	std::cout << "------------- Owner: " << list.owner << std::endl;
	this->_root.getUI().clearConversationList();
	for (int i = 0; i < 8; i++) {
		if (!*(list.clients[i]))
			break;
		std::cout << "-------------  Client: " << i + 1 << ". " << list.clients[i] << std::endl;
		this->_root.getUI().appendToConversationList(list.clients[i]);
		listContactStr.push_back(list.clients[i]);
	}

	if (listContactStr.size() == 1)
		this->_root.getUI().updateNameCallingText(listContactStr[0]);
	else if (listContactStr.size() > 1)
		this->_root.getUI().updateNameCallingText(listContactStr[0], std::vector<std::string>(listContactStr.begin() + 1, listContactStr.end()));

	this->_root.getCall().getCurrentCall().setIdConv(list.idConv);
	this->_root.getUI().refreshStatusWhenReceivingCall();
	this->_root.getUI().showWindow("ReceiveCallDiag");
}

///////////////////
//
// NOTIFICATIONS //
//
///////////////////

void    babel::NetworkManager::C_NotifyLeaveCall(babel::t_babelPackedData& t)
{
	std::cout << "NOTIFICATION : USER HAS LEAVE CALL (" << t.code << ")" << std::endl;

	char                    clientLeft[32];

	std::copy_n(t.data.data(), 32, clientLeft);

    if (!(*(clientLeft)))
        return;

    std::cout << "-------> USER LEFT: " << clientLeft << std::endl;

    this->_root.getUI().removeToConversationlist(clientLeft);
    this->_root.getUI().refreshWhenSomeoneLeavingCall();
}

void    babel::NetworkManager::C_NotifyUserJoinConv(babel::t_babelPackedData& t)
{
	std::cout << "NOTIFICATION : USER HAS JOINED CALL(" << t.code << ")" << std::endl;

	babel::t_clientCallJoin	join	= *(reinterpret_cast<babel::t_clientCallJoin*>(t.data.data()));
	t_clientCallStruct		client	= join.client;

    if (!(*(join.client.login)))
		return;

    this->_root.getUI().appendToConversationList(client.login);
    this->_root.getUI().refreshWhenJoiningCall();

	std::cout << "------------- User informations: " << client.login << " / " << client.ip << " / " << client.port << std::endl;
}
