#ifndef __MEMORY_INTERFACE_H__
#define __MEMORY_INTERFACE_H__
#include "commondef.h"

// define interface type
#define interface struct

// class CMemoryBlock<T>
template< typename T >
class CMemoryBlock
{
public:
	CMemoryBlock<T>();

	~CMemoryBlock<T>();

	bool	Initalize(const int nInitSize);

	T*		GetMemory();

	int		GetMaxMemorySize() const;

	int		GetCanUseMemorySize() const;

	void	Release();
private:
	T*	m_pAddress;		// malloc(sizeof(T)*m_nMaxSize)
	int	m_nUseSize;
	int m_nMaxSize;
};

template< typename T >
CMemoryBlock<T>::CMemoryBlock()
{
	m_pAddress = NULL;
	m_nUseSize = 0;
	m_nMaxSize = 0;
}

template< typename T >
CMemoryBlock<T>::~CMemoryBlock()
{
	Release();
}

template< typename T >
bool CMemoryBlock<T>::Initalize(const int nInitSize)
{	
	if (nInitSize <= m_nMaxSize)	// 未超出原来内存，重置即可
	{
		m_nUseSize = nInitSize;
		memset(m_pAddress, 0, sizeof(T) * m_nUseSize);
		return true;
	}

	m_pAddress = new T[nInitSize];
	if (NULL == m_pAddress)
		return false;

	m_nUseSize = nInitSize;
	m_nMaxSize = nInitSize;
	memset(m_pAddress, 0, sizeof(T) * m_nUseSize);

	return true;
}

template< typename T >
T* CMemoryBlock<T>::GetMemory()
{
	return m_pAddress;
}

template< typename T >
int CMemoryBlock<T>::GetMaxMemorySize() const
{
	return m_nMaxSize;
}

template< typename T >
int CMemoryBlock<T>::GetCanUseMemorySize() const
{
	return m_nUseSize;
}

template< typename T >
void CMemoryBlock<T>::Release()
{
	if (NULL != m_pAddress)
		delete[] m_pAddress;

	m_pAddress = NULL;
	m_nUseSize = 0;
	m_nMaxSize = 0;
}

// class IMemoryBlockMgr
class IMemoryBlockMgr
{
	virtual CMemoryBlock<char> GetFileContentBlock() = 0;
};




#endif // __MEMORY_INTERFACE_H__