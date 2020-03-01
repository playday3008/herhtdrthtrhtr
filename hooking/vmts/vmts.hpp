#pragma once

class CVMT {
	// (c) wzn
	void SetSize( ) {
		m_iSize = 0;

		auto pAddress = m_pOriginal[ m_iSize ];
		if ( !pAddress )
		{
			return;
		}

		if ( pAddress < 0x1000 || pAddress > 0xFFE00000 )
		{
			return;
		}

		auto bIsSafeAddress = [ & ]( int index ) -> bool 
		{
			auto pAddress = m_pOriginal[ index ];
			if ( !pAddress )
			{
				return false;
			}

			if ( pAddress < 0x1000 || pAddress > 0xFFE00000 )
			{
				return false;
			}

			MEMORY_BASIC_INFORMATION mInfo;
			if ( !VirtualQuery( reinterpret_cast< void* >( pAddress ), &mInfo, sizeof mInfo ) )
			{
				return false;
			}

			return mInfo.Protect != 0x1;
		};

		m_iSize = 0;
		while ( bIsSafeAddress( m_iSize ) )
		{
			m_iSize++;
		}
	}

	uintptr_t** m_pBase = nullptr;
	uintptr_t* m_pNew = nullptr;
	uintptr_t* m_pOriginal = nullptr;
	int m_iSize = 0;
public:
	CVMT( void* pBase ) {
		Initialize( pBase );
	}
	~CVMT( ) {
		Release( );
	}

	// FIXME: utilize bool functionality for error handling
	bool Initialize( void* pBase ) {
		m_pBase = reinterpret_cast< uintptr_t ** >( pBase );

		if ( !m_pBase )
		{
			return false;
		}

		m_pOriginal = *m_pBase;

		if ( !m_pOriginal )
		{
			return false;
		}

		SetSize( );

		if ( !m_iSize )
		{
			return false;
		}

		m_pNew = new ( std::nothrow ) uintptr_t[ m_iSize ];

		if ( !m_pNew )
		{
			return false;
		}

		std::memcpy( m_pNew, m_pOriginal, m_iSize * sizeof( uintptr_t ) );
		*m_pBase = m_pNew;

		return true;
	}

	void Release( ) const {
		if ( !m_pOriginal || !m_pNew || !m_iSize )
		{
			return;
		}

		*m_pNew = *m_pOriginal; // *m_pBase = m_pOriginal
		delete[ ] m_pNew;
	}

	uintptr_t Release( int iIndex ) const {
		if ( !m_pOriginal || !m_pNew || !m_iSize )
		{
			return 0;
		}

		m_pNew[ iIndex ] = m_pOriginal[ iIndex ];
		return m_pOriginal[ iIndex ];
	}

	template < typename T >
	T Hook( void* pFunc, int iIndex ) const {
		if ( m_iSize < iIndex )
		{
			return 0;
		}

		m_pNew[ iIndex ] = reinterpret_cast< uintptr_t >( pFunc );
		return reinterpret_cast< T >( m_pOriginal[ iIndex ] );
	}

	template < typename T >
	T Get( int iIndex ) const {
		if ( m_iSize < iIndex )
		{
			return 0;
		}

		return reinterpret_cast< T >( m_pOriginal[ iIndex ] );
	}

	uintptr_t Get( int iIndex ) const {
		if ( m_iSize < iIndex )
		{
			return 0;
		}

		return m_pOriginal[ iIndex ];
	}
};