//#include "Factory.h"
//#include"Enemy.h"
//#include"Player.h"
//
//Factory* Factory::s_Instance = nullptr;
//
//void Factory::RegisterType(string className, function<GameObject* (Properties* props)> type) {
//	m_TypeRigistry[className] = type;
//}
//
//GameObject* Factory::CreateObject(string type, Properties* props) {
//
//	GameObject* object = nullptr;
//	auto it = m_TypeRigistry.find(type);
//
//	if (it != m_TypeRigistry.end()) {
//		object = it->second(props);
//	}
//
//	return object;
//}