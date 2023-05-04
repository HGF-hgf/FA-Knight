//#pragma once
//
//#include"INCLUDE.h"
//#include"GameObject.h"
//
//using namespace std;
//
//
//class Factory {
//public:
//	GameObject* CreateObject(string type, Properties* props);
//	void RegisterType(string className, function < GameObject* (Properties* props)> type);
//	static Factory* Getinstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Factory(); }
//
//
//private:
//	Factory(){}
//	static Factory* s_Instance;
//	map<string, function<GameObject* (Properties* props)>> m_TypeRigistry;
//};
//
//
//template <class Type>
//class Registrar {
//public:
//	Registrar(string className) {
//		Factory::Getinstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
//	}
//};
