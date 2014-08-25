#include "StdAfx.h"
#include ".\ColumnListContainerElementUI.h"


namespace DuiLib{
CColumnListContainerElementUI::CColumnListContainerElementUI(void)
{
}

CColumnListContainerElementUI::~CColumnListContainerElementUI(void)
{
}

void CColumnListContainerElementUI::DoPaint( HDC hDC, const RECT& rcPaint )
{
	if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;

	RECT rcTemp = { 0 };
	if( !::IntersectRect(&rcTemp, &rcPaint, &m_rcItem) ) return;

	CRenderClip clip;
	CRenderClip::GenerateClip(hDC, rcTemp, clip);
	CControlUI::DoPaint(hDC, rcPaint);

	//DrawItemBk(hDC, m_rcItem);

	if( m_items.GetSize() > 0 ) {
		RECT rc = m_rcItem;
		rc.left += m_rcInset.left;
		rc.top += m_rcInset.top;
		rc.right -= m_rcInset.right;
		rc.bottom -= m_rcInset.bottom;
		if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) rc.right -= m_pVerticalScrollBar->GetFixedWidth();
		if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) rc.bottom -= m_pHorizontalScrollBar->GetFixedHeight();

		if( !::IntersectRect(&rcTemp, &rcPaint, &rc) ) {
			for( int it = 0; it < m_items.GetSize(); it++ ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
				if( !pControl->IsVisible() ) continue;
				if( !::IntersectRect(&rcTemp, &rcPaint, &pControl->GetPos()) ) continue;
				if( pControl ->IsFloat() ) {
					if( !::IntersectRect(&rcTemp, &m_rcItem, &pControl->GetPos()) ) continue;
					pControl->DoPaint(hDC, rcPaint);
				}
			}
		}
		else {
			CRenderClip childClip;
			CRenderClip::GenerateClip(hDC, rcTemp, childClip);
			for( int it = 0; it < m_items.GetSize(); it++ ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
				if( !pControl->IsVisible() ) continue;
				if( !::IntersectRect(&rcTemp, &rcPaint, &pControl->GetPos()) ) continue;
				if( pControl ->IsFloat() ) {
					if( !::IntersectRect(&rcTemp, &m_rcItem, &pControl->GetPos()) ) continue;
					CRenderClip::UseOldClipBegin(hDC, childClip);
					pControl->DoPaint(hDC, rcPaint);
					CRenderClip::UseOldClipEnd(hDC, childClip);
				}
				else {
					if( !::IntersectRect(&rcTemp, &rc, &pControl->GetPos()) ) continue;
					pControl->DoPaint(hDC, rcPaint);
				}
			}
		}
	}

	if( m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible() ) {
		if( ::IntersectRect(&rcTemp, &rcPaint, &m_pVerticalScrollBar->GetPos()) ) {
			m_pVerticalScrollBar->DoPaint(hDC, rcPaint);
		}
	}

	if( m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible() ) {
		if( ::IntersectRect(&rcTemp, &rcPaint, &m_pHorizontalScrollBar->GetPos()) ) {
			m_pHorizontalScrollBar->DoPaint(hDC, rcPaint);
		}
	}
}

}