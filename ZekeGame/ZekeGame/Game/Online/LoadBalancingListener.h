#pragma once
#include "LoadBalancing-cpp/inc/Client.h"
#include "BaseView.h"

#define PLAYER_UPDATE_INTERVAL_MS 500

using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

struct LocalPlayer
{
	LocalPlayer();
	int x;
	int y;
	int z;
	unsigned long lastUpdateTime;
};

class LoadBalancingListener : public ExitGames::LoadBalancing::Listener
{
public:
	LoadBalancingListener(BaseView* pView);
	~LoadBalancingListener();
	void setLBC(ExitGames::LoadBalancing::Client* pLbc);
	void connect(const ExitGames::Common::JString& userName);
	void disconnect();
	void createRoom(void);
	void service();
	//何らかのイベントを送信する関数を定義
	void raiseSomeEvent();
	//モンスターのデータを送る。
	void raiseMonData();
	void raiseMonAIs();
	void raiseVisualAIsData();
	void raiseRating();
	//
	int GetOnlinePlayerCount() {
		return mpLbc->getCountPlayersOnline();
	}

	/*
	送るモンスターのデータをセットする
	args:
		num:何番目のモンスターか
		monID:モンスターのID
	*/
	void SetMonData(int num, int monID)
	{
		m_monNUM = num;
		m_monID = monID;
	}

	void SetText(const char* text,int id)
	{
		delete[] m_text[id];
		m_text[id] = (char*)malloc(sizeof(char)*(strlen(text) + 1));
		strcpy(m_text[id], text);
	}

	void SetVisualAiData(JString data, int id) {
		nByte idkey = 104;
		nByte datakey = 109;
		m_visualAisData[id] = data;
		m_datas[id].put(idkey, id);
		m_datas[id].put(datakey, data);
	/*	delete[] m_visualAisData[id];
		m_visualAisData[id] = (char*)malloc(sizeof(char) * (sizeof(data) + 1));
		strcpy(m_visualAisData[id], data);*/
		//for (int i = 0; i < 1024; i++) {
		//	m_visualAisData[id][i] = data[i];
		//}
		//datas[id].put((nByte)104, id);
		//datas[id].put((nByte)109, data,1024);
	}
	int* GetEnemyAiModes() {
		return m_enemyAimode;
	}
	void SetAiMode(int aimode, int id) {
		m_aimode[id] = aimode;
	}
	//送られてきたモンスターのナンバーをかえす。
	int GetMonNum()
	{
		return m_hangMNUM;
	}
	bool isGotEnemyPythonCodes();
	//送られてきたモンスターのIDを返す。
	int GetMonID()
	{
		return m_hangMID;
	}


	//繋がっていますか
	bool isConect()
	{
		return misConect;
	}

	//データが送られてきているかどうか。
	//あんたを探してたんだ。
	bool isHang()
	{
		return misHang;
	}

	bool CanStartGame() {
		return m_isEnemyLoadedMyData && isGotEnemyPythonCodes();
	}
	
	bool isEnemyLoadedMydata() {
		return m_isEnemyLoadedMyData;
	}

	void SetEnemyLoadedMyDate(bool flag) {
		m_isEnemyLoadedMyData = flag;
	}

	bool raiseMyLoadingState();
	//012 
	void SetTeamMonsterInfo(int info[3]);
	float GetEnemyRate() {
		return m_enemyRate;
	}
	int* GetEnemyTeamIDs() {
		return m_enemyTeamData;
	}
	bool isJoining() { return m_isJoining; }
	void DataReset();

	bool isEnemyAbandoned(){
		return 	m_enemyAbandoned;
	}
private:
	//From Common::BaseListener

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);
	virtual void onRoomListUpdate(void);
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes);

	void updateState(void);
	void afterRoomJoined(int localPlayerNr);
private:
	enum EnEvetCode
	{
		enText = 5,
		enMonData,
		enRateData,
		enVisualAiData,
		enLoadState,
	};

	int m_toRaiseTeamData[3] = { 0 , 0 , 0};
	int m_enemyTeamData[3] = { -1 , -1 , -1 };
	std::string m_pythonCode;
	ExitGames::LoadBalancing::Client* mpLbc;
	BaseView* mpView;
	int mMap = 1;	//ルーム作成時に使うKey
	int m_val = 10; //送信する値などを適当に定義
	int m_maxPlayer = 2;

	int m_monNUM = 0;	//モンスターのナンバー
	int m_monID = 0;			//モンスターのID

	int m_hangMNUM = 0;	//送られてきたモンスターのナンバー
	int m_hangMID = 0;	//送られてきたモンスターのID

	char* m_text[3] = { nullptr, nullptr, nullptr }; //送るテキストデータ。
	JString m_visualAisData[3];
	char* m_hangPY = nullptr; //送られて来たテキストデータ。
	int m_aimode[3] = { 0,0,0 }; //送るAIモード
	int m_enemyAimode[3] = { 0,0,0 }; //送られてきたenemy Ai Mode(VA)
	int mLocalPlayerNr; //Photonから自分に割り振られたプレイヤーナンバー
	LocalPlayer mLocalPlayer;
	
	bool misConect = false;		//つながってる〜？
	bool m_enemyAbandoned = false;
	bool misHang = false;		//何か送られてきてる？
	bool m_isEnemyLoadedMyData = false;
	bool m_isAiLoaded[3] = { false, false, false };
	float m_enemyRate = 0.f;
	bool m_isJoining = false;
	Hashtable m_datas[3];
};

