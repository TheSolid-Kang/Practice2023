#pragma once

template<typename Key, typename Value>
class CNode {
public:
	CNode(Key _key, Value _value)
		: m_key(_key), m_value(_value) { }
	Key m_key;
	Value m_value;
	CNode<Key, Value>* m_nextNode;
};

template<typename Key, typename Value>
class CLinkedList {
public:
	~CLinkedList() {
		while (nullptr != (*m_pRootNode).m_nextNode) {
			CNode<Key, Value>* pCurNode = m_pRootNode;
			m_pRootNode = (*m_pRootNode).m_nextNode;
			delete pCurNode;
		}
	}
private:
	size_t m_curSize = 0;
	CNode<Key, Value>* m_pRootNode;

public:
	void Add(const Key& _key, const Value& _value) noexcept {
		if (nullptr == m_pRootNode) {
			m_pRootNode = new CNode<Key, Value>(_key, _value);
		} 
		else { //nullptr != m_pRootNode
			CNode<Key, Value>* pCurNode = m_pRootNode;
			while (nullptr != (*pCurNode).m_nextNode) {
				pCurNode = (*pCurNode).m_nextNode;
			}
			(*pCurNode).m_nextNode = new CNode<Key, Value>(_key, _value);
		}
		++m_curSize;
	}
	Value Get(const Key& _key) {
		CNode<Key, Value>* pCurNode = m_pRootNode;
		while (nullptr != (*pCurNode).m_nextNode && _key != (*pCurNode).m_key) {
			pCurNode = (*pCurNode).m_nextNode;
		}

		if ((*pCurNode).m_key != _key) {
			return nullptr;
		}

		return (*pCurNode).m_value;
	}

	size_t Size() {
		return m_curSize;
	}
	CNode<Key, Value>* GetRootNode() noexcept {
		return m_pRootNode;
	}
};
#define DEFAULT_CAP 32
template<typename Key, typename Value>
class CHashMap
{
public:
	CHashMap() {
		for (int i = 0; i < DEFAULT_CAP; i++) {
			m_pConrainer[i] = new CLinkedList<Key, Value>();
		}
	}
	~CHashMap() {
		delete[] m_pConrainer;
	}
private:
	CLinkedList<Key, Value>* m_pConrainer[DEFAULT_CAP];
	
private:
	int Hashing(Key _key) {
		int hashValue = 0;

		for (char _ch : _key) {
			hashValue += (int)_ch;
		}
		hashValue %= DEFAULT_CAP;
		return hashValue;
	}
	CNode<Key, Value>* FindNodeByKey(Key _key, CNode<Key, Value>* _pCursorNode) {
		CNode<Key, Value>* pCursorNode = _pCursorNode;
		while (nullptr != pCursorNode) {
			if ((*pCursorNode).m_key == _key) {
				break;
			}
			pCursorNode = (*pCursorNode).m_nextNode;
		}
		return pCursorNode;
	}
public:
	void Put(Key _key, Value _value) {
		int hashCode = (*this).Hashing(_key);

		CNode<Key, Value>* pCursorNode = (*(*this).m_pConrainer[hashCode]).GetRootNode();
		pCursorNode = (*this).FindNodeByKey(_key, pCursorNode);

		// 해쉬코드 컨테이너에 키가 있다면
		if (nullptr != pCursorNode) {
			// 덮어쓰기
			(*pCursorNode).m_value = _value;
		}
		else { // 컨테이너에 키가 없다면
			// 컨테이너에 노드추가
			(*(*this).m_pConrainer[hashCode]).Add(_key, _value);
		}
	}
	Value Get(Key _key) {
		int hashCode = (*this).Hashing(_key);

		CNode<Key, Value>* pCursorNode = (*(*this).m_pConrainer[hashCode]).GetRootNode();
		pCursorNode = (*this).FindNodeByKey(_key, pCursorNode);

		// 해쉬코드 컨테이너에 키가 있다면
		if (pCursorNode != nullptr) {
			// 값 리턴
			return pCursorNode->m_value;
		}
		// 없다면
		else {
			//std::cout << "키를 찾을 수 없습니다." << std::endl;
			return nullptr;
		}
	}



};

