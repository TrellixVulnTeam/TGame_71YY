#include "stdafx.h"
#include "BaseView.h"
#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "TestView.h"

using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

static int randomColor(int from = 0, int to = 256)
{
	int r = from + rand() % (to - from);
	int g = from + rand() % (to - from);
	int b = from + rand() % (to - from);
	return (r << 16) + (g << 8) + b;
}

const JString PeerStatesStr[] = {
	L"Uninitialized",
	L"PeerCreated",
	L"ConnectingToNameserver",
	L"ConnectedToNameserver",
	L"DisconnectingFromNameserver",
	L"Connecting",
	L"Connected",
	L"WaitingForCustomAuthenticationNextStepCall",
	L"Authenticated",
	L"JoinedLobby",
	L"DisconnectingFromMasterserver",
	L"ConnectingToGameserver",
	L"ConnectedToGameserver",
	L"AuthenticatedOnGameServer",
	L"Joining",
	L"Joined",
	L"Leaving",
	L"Left",
	L"DisconnectingFromGameserver",
	L"ConnectingToMasterserver",
	L"ConnectedComingFromGameserver",
	L"AuthenticatedComingFromGameserver",
	L"Disconnecting",
	L"Disconnected"
};

// TODO: update PeerStatesStr when PeerStates changes
// Checker below checks count match only
class PeerStatesStrChecker
{
public:
	PeerStatesStrChecker(void)
	{
		DEBUG_ASSERT(sizeof(PeerStatesStr) / sizeof(JString) == PeerStates::Disconnected + 1);
	}
} checker;

LocalPlayer::LocalPlayer(void) : x(0), y(0), color(randomColor(100)), lastUpdateTime(0)
{
}

LoadBalancingListener::LoadBalancingListener(BaseView* pView)
{
	mpLbc = NULL;
	mpView = pView;
}

LoadBalancingListener::~LoadBalancingListener(void)
{
	delete mpView;
}

void LoadBalancingListener::setLBC(ExitGames::LoadBalancing::Client* pLbc)
{
	this->mpLbc = pLbc;
}

void LoadBalancingListener::connect(const JString& userName)
{
	mpLbc->connect(AuthenticationValues().setUserID(JString() + GETTIMEMS()), userName);
}

void LoadBalancingListener::disconnect() {
	mpLbc->disconnect();
}


void LoadBalancingListener::debugReturn(int debugLevel, const JString& string)
{
	Console::get().debugReturn(debugLevel, string);
}

void LoadBalancingListener::connectionErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"connection failed with error ") + errorCode);
	updateState();
}

void LoadBalancingListener::clientErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + L" from client");
	updateState();
}

void LoadBalancingListener::warningReturn(int warningCode)
{
	Console::get().writeLine(JString(L"received warning ") + warningCode + " from client");
}

void LoadBalancingListener::serverErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + " from server");
	updateState();
}

void LoadBalancingListener::joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player)
{
	Console::get().writeLine(JString("player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void LoadBalancingListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	if (isInactive)
		Console::get().writeLine(JString(L"player ") + playerNr + L" has suspended the game");
	else
	{
		Console::get().writeLine(JString(L"player ") + playerNr + L" has abandoned the game");
	}
}

void LoadBalancingListener::customEventAction(int playerNr, nByte eventCode, const Object& eventContentObj)
{
	// logging the string representation of the eventContent can be really useful for debugging, but use with care: for big events this might get expensive
	//EGLOG(ExitGames::Common::DebugLevel::ALL, L"an event of type %d from player Nr %d with the following content has just arrived: %ls", eventCode, playerNr, eventContent.toString(true).cstr());

	switch (eventCode)
	{
	case 1:
	{
		//�R���e���c�̃R�s�[�ɃA�N�Z�X
		ExitGames::Common::Hashtable content = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
		//�A�h���X�ŃA�N�Z�X���܂��i���̊֐����Ԃ�Ƃ����ɖ����ɂȂ邽�߁A��ŃA�N�Z�X�𑱂���K�v������f�[�^�̂��ׂĂ̕������R�s�[����K�v������܂��j
		//ExitGames::Common::Hashtable* pContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataAddress();
	}
	break;
	case 2:
	{
		//�������A�y�C���[�h�̓n�b�V���e�[�u���ł���K�v�͂���܂���B�P����64�r�b�g�����̂悤�ɑ��M����̂͂ǂ��ł����H
		float content = ExitGames::Common::ValueObject<float>(eventContentObj).getDataCopy();
		char message[256];
		float pos = content;
		sprintf_s(message, "get event code pos %f\n", pos);
		OutputDebugStringA(message);
	}
	break;
	case 3:
	{
		// ���������_���̔z��ł����H
		float* pContent = ExitGames::Common::ValueObject<float*>(eventContentObj).getDataCopy();
		float** ppContent = ExitGames::Common::ValueObject<float*>(eventContentObj).getDataAddress();
		short contentElementCount = *ExitGames::Common::ValueObject<float*>(eventContentObj).getSizes();
		//�z����y�C���[�h�Ƃ��ĕێ�����I�u�W�F�N�g��getDataCopy�i�j���Ăяo���Ƃ��́A
		//deallocateArray�i�j���g�p���Ĕz��̃R�s�[�������Ŋ��蓖�ĉ�������K�v������܂��B
		ExitGames::Common::MemoryManagement::deallocateArray(pContent);
	}
	break;
	default:
	{
		//���������ꂽ�f�[�^�^�𑗎�M������@�̃R�[�h��ɂ��ẮA
		//C ++�N���C�A���gSDK����demo_typeSupport���Q�Ƃ��Ă�������
	}
	break;
	}
}

void LoadBalancingListener::connectReturn(int errorCode, const JString& errorString, const JString& region, const JString& cluster)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"connected to cluster " + cluster + L" of region " + region);
		mpLbc->opJoinRandomRoom();
	}
	else
		Console::get().writeLine(JString(L"Warn: connect failed ") + errorCode + L" " + errorString);
}

void LoadBalancingListener::disconnectReturn(void)
{
	updateState();
	Console::get().writeLine(L"disconnected");
}

void LoadBalancingListener::createRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been created");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinOrCreateRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been entered");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opJoinOrCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRandomRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::NO_MATCH_FOUND)
		createRoom();
	else if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRandomRoom() failed: " + errorString);
}

void LoadBalancingListener::leaveRoomReturn(int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
		Console::get().writeLine(L"game room has been successfully left");
	else
		Console::get().writeLine(L"opLeaveRoom() failed: " + errorString);
}

void LoadBalancingListener::gotQueuedReturn(void)
{
	updateState();
}

void LoadBalancingListener::joinLobbyReturn(void)
{
	Console::get().writeLine(L"joined lobby");
	updateState();
}

void LoadBalancingListener::leaveLobbyReturn(void)
{
	Console::get().writeLine(L"left lobby");
	updateState();
}

void LoadBalancingListener::onLobbyStatsUpdate(const JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats update");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());

	// lobby stats request test
	JVector<LobbyStatsRequest> ls;
	ls.addElement(LobbyStatsRequest());
	ls.addElement(LobbyStatsRequest(L"AAA"));
	ls.addElement(LobbyStatsRequest(L"BBB"));
	ls.addElement(LobbyStatsRequest(L"CCC", LobbyType::DEFAULT));
	ls.addElement(LobbyStatsRequest(L"AAA", LobbyType::SQL_LOBBY));
	mpLbc->opLobbyStats(ls);
}

void LoadBalancingListener::onLobbyStatsResponse(const ExitGames::Common::JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats response");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());
}

void LoadBalancingListener::onRoomListUpdate()
{
	const JVector<Room*>& rooms = mpLbc->getRoomList();
	JVector<JString> names(rooms.getSize());
	for (unsigned int i = 0; i < rooms.getSize(); ++i)
		names.addElement(rooms[i]->getName());
	//mpView->updateRoomList(names);
}

void LoadBalancingListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
}

void LoadBalancingListener::updateState()
{
	int state = mpLbc->getState();
	mpView->updateState(state, PeerStatesStr[state], state == PeerStates::Joined ? mpLbc->getCurrentlyJoinedRoom().getName() : JString());
}


void LoadBalancingListener::afterRoomJoined(int localPlayerNr)
{
	
}

void LoadBalancingListener::createRoom()
{
	JString name =
#ifdef __UNREAL__
		JString(L"UE-")
#else
		JString(L"native-")
#endif
		+ (rand() % 100);
	Hashtable props;
	props.put(L"m", mMap);
	mpLbc->opCreateRoom(name, RoomOptions().setCustomRoomProperties(props));
	Console::get().writeLine(L"Creating room " + name);
}

void LoadBalancingListener::service()
{
	unsigned long t = GETTIMEMS();
	if ((t - mLocalPlayer.lastUpdateTime) > PLAYER_UPDATE_INTERVAL_MS)
	{
		mLocalPlayer.lastUpdateTime = t;
		if (mpLbc->getState() == PeerStates::Joined) {
			//���t���[���Ă΂�鏈��
			move();
		}
	}
}

//�������낢��
void LoadBalancingListener::raisePlayerPos() {
	nByte eventCode = 2;
	ExitGames::Common::Hashtable evData;
	evData.put((nByte)1, m_posy);
	bool sendReliable = true;
	mpLbc->opRaiseEvent(sendReliable, m_posy, eventCode);
	char message[256];
	float pos = m_posy;
	sprintf_s(message, "raise pos %f\n", pos);
	OutputDebugStringA(message);
}

void LoadBalancingListener::move() {
	if (g_pad[0].IsPress(enButtonY)) {
		m_posy += 10.0f;
		raisePlayerPos();
	}
}
void LoadBalancingListener::raiseSomeEvent() {
	//���܂��܂Ȏ�ނ̃C�x���g�i�u�ړ��v�A�u�B�e�v�Ȃǁj����ʂ��邽�߂�
	//�ʌ̃C�x���g�R�[�h���g�p����
	nByte eventCode = 2; 
	//Photons�̃V���A�����ɂ���ăT�|�[�g����Ă������A
	//�D���ȕ��@�Ńy�C���[�h�f�[�^�𐮗����܂�
	ExitGames::Common::Hashtable evData;
	evData.put((nByte)1, m_val);
	//�ǂ��ɂł���������K�v������ꍇ�́A�M���ł�����̂𑗐M���܂�
	bool sendReliable = false;
	mpLbc->opRaiseEvent(sendReliable, evData, eventCode);
}
