
// Sokoban_ver_MFCDoc.cpp : implementation of the CSokobanverMFCDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sokoban_ver_MFC.h"
#endif

#include "Sokoban_ver_MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSokobanverMFCDoc

IMPLEMENT_DYNCREATE(CSokobanverMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CSokobanverMFCDoc, CDocument)
END_MESSAGE_MAP()


// CSokobanverMFCDoc construction/destruction

CSokobanverMFCDoc::CSokobanverMFCDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSokobanverMFCDoc::~CSokobanverMFCDoc()
{
}

BOOL CSokobanverMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CROW = CCOLUMN = 0;
	CStep = 0;
	CMapNo = "";
	CWall.clear();
	CBox.clear();
	CDest.clear();
	CArrival.clear();
	CWorker.clear();
	LoadMap(1);

	return TRUE;
}





void CSokobanverMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << CROW << CCOLUMN << CStep << Corder << CMapNumber;

		ar << CWall.size();
		for (size_t i = 0; i < CWall.size(); ++i)
			ar << CWall[i].Ccharator << CWall[i].Cy << CWall[i].Cx;

		ar << CBox.size();
		for (size_t i = 0; i < CBox.size(); ++i)
			ar << CBox[i].Ccharator << CBox[i].Cy << CBox[i].Cx;

		ar << CDest.size();
		for (size_t i = 0; i < CDest.size(); ++i)
			ar << CDest[i].Ccharator << CDest[i].Cy << CDest[i].Cx;

		ar << CArrival.size();
		for (size_t i = 0; i < CArrival.size(); ++i)
			ar << CArrival[i].Ccharator << CArrival[i].Cy << CArrival[i].Cx;

		ar << CWorker.size();
		for (size_t i = 0; i < CWorker.size(); ++i)
			ar << CWorker[i].Ccharator << CWorker[i].Cy << CWorker[i].Cx;

		ar << CBlank.size();
		for (size_t i = 0; i < CBlank.size(); ++i)
			ar << CBlank[i].Ccharator << CBlank[i].Cy << CBlank[i].Cx;
	}
	else
	{
		ar >> CROW >> CCOLUMN >> CStep >> Corder >> CMapNumber;

		CWall.clear();
		CBox.clear();
		CDest.clear();
		CArrival.clear();
		CWorker.clear();
		CBlank.clear();

		size_t size;
		char charater;
		int y, x;

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CWall.push_back(Coordinate(charater, y, x));
		}

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CBox.push_back(Coordinate(charater, y, x));
		}

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CDest.push_back(Coordinate(charater, y, x));
		}

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CArrival.push_back(Coordinate(charater, y, x));
		}

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CWorker.push_back(Coordinate(charater, y, x));
		}

		ar >> size;
		for (size_t i = 0; i < size; i++)
		{
			ar >> charater >> y >> x;
			CBlank.push_back(Coordinate(charater, y, x));
		}
	}
}



#ifdef _DEBUG
void CSokobanverMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSokobanverMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 



bool CSokobanverMFCDoc::Contral(char c)
{
    Corder = c;

    //restar
    if (Corder == 'R')
    {
        LoadMap(CMapNumber);
        Arrive();

        return true;
    }

    else if (Corder == 'K' || Corder == 'J' || Corder == 'H' || Corder == 'L' ||
             Corder == 'W' || Corder == 'S' || Corder == 'A' || Corder == 'D' ||
             Corder == VK_UP || Corder == VK_DOWN || Corder == VK_LEFT || Corder == VK_RIGHT)
    {
        if (MoveWorker())
            return true;

        else
            return false;
    }

    //pass
    else if (Corder == 'P' || Corder == VK_NEXT)
    {
        if (CMapNumber < 150)
            LoadMap(CMapNumber + 1);
        return true;
    }

    //last
    else if (Corder == 'O' || Corder == VK_PRIOR)
    {
        int hold = CMapNumber;

        if (CMapNumber > 0)
        {
            LoadMap(CMapNumber - 1);

            if (CMapNumber == hold)
                LoadMap(CMapNumber - 2);
        }

        return true;
    }
}


bool CSokobanverMFCDoc::MoveWorker()
{
    if (Corder == 'K' || Corder == 'W' || Corder == VK_UP)
    {
        if (NextToWorker(UP))
        {
            CWorker[0].Cy--;
            CStep++;

            return true;
        }
    }

    else if (Corder == 'J' || Corder == 'S' || Corder == VK_DOWN)
    {
        if (NextToWorker(DOWN))
        {
            CWorker[0].Cy++;
            CStep++;

            return true;
        }
    }

    else if (Corder == 'H' || Corder == 'A' || Corder == VK_LEFT)
    {
        if (NextToWorker(LEFT))
        {
            CWorker[0].Cx--;
            CStep++;

            return true;
        }
    }

    else if (Corder == 'L' || Corder == 'D' || Corder == VK_RIGHT)
    {
        if (NextToWorker(RIGHT))
        {
            CWorker[0].Cx++;
            CStep++;

            return true;
        }
    }

    return false;
}


bool CSokobanverMFCDoc::NextToWorker(Direction d)
{
    switch (d)
    {
    case UP:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy - 1 && CWall[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy - 1 && CBox[i].Cx == CWorker[0].Cx)
            {
                if (NextNextToWorker(d))
                {
                    CBox[i].Cy--;
                    return true;
                    break;
                }

                else
                {
                    return false;
                    break;
                }
            }
        }

        return true;
        break;

    case DOWN:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy + 1 && CWall[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy + 1 && CBox[i].Cx == CWorker[0].Cx)
            {
                if (NextNextToWorker(d))
                {
                    CBox[i].Cy++;
                    return true;
                    break;
                }

                else
                {
                    return false;
                    break;
                }
            }
        }

        return true;
        break;

    case LEFT:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy && CWall[i].Cx == CWorker[0].Cx - 1)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy && CBox[i].Cx == CWorker[0].Cx - 1)
            {
                if (NextNextToWorker(d))
                {
                    CBox[i].Cx--;
                    return true;
                    break;
                }

                else
                {
                    return false;
                    break;
                }
            }
        }

        return true;
        break;

    case RIGHT:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy && CWall[i].Cx == CWorker[0].Cx + 1)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy && CBox[i].Cx == CWorker[0].Cx + 1)
            {
                if (NextNextToWorker(d))
                {
                    CBox[i].Cx++;
                    return true;
                    break;
                }

                else
                {
                    return false;
                    break;
                }
            }
        }

        return true;
        break;
    }

    return false;
}


bool CSokobanverMFCDoc::NextNextToWorker(Direction d)
{
    switch (d)
    {
    case UP:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy - 2 && CWall[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy - 2 && CBox[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        return true;
        break;

    case DOWN:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy + 2 && CWall[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy + 2 && CBox[i].Cx == CWorker[0].Cx)
            {
                return false;
                break;
            }
        }

        return true;
        break;

    case LEFT:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy && CWall[i].Cx == CWorker[0].Cx - 2)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy && CBox[i].Cx == CWorker[0].Cx - 2)
            {
                return false;
                break;
            }
        }

        return true;
        break;

    case RIGHT:

        for (size_t i = 0; i < CWall.size(); i++)
        {
            if (CWall[i].Cy == CWorker[0].Cy && CWall[i].Cx == CWorker[0].Cx + 2)
            {
                return false;
                break;
            }
        }

        for (size_t i = 0; i < CBox.size(); i++)
        {
            if (CBox[i].Cy == CWorker[0].Cy && CBox[i].Cx == CWorker[0].Cx + 2)
            {
                return false;
                break;
            }
        }

        return true;
        break;
    }

    return false;
}


bool CSokobanverMFCDoc::Arrive()
{
    //initialize
    CArrival.clear();

    for (size_t i = 0; i < CBox.size(); i++)
    {
        for (size_t j = 0; j < CDest.size(); j++)
        {
            if (CBox[i].Cy == CDest[j].Cy && CBox[i].Cx == CDest[j].Cx)
            {
                CArrival.push_back(Coordinate(arrive_character, CBox[i].Cy, CBox[i].Cx));
                break;
            }
        }
    }

    if (CArrival.size() == CDest.size()) return true;
    else                         return false;
}


bool CSokobanverMFCDoc::LoadMap(int n)
{
    if (1 <= n <= 150)
    {
        //initialize
        CMapNumber = n;
        CROW = CCOLUMN = 0;
        CStep = 0;
        CMapNo = "";
        CBlank.clear();
        CWall.clear();
        CBox.clear();
        CDest.clear();
        CArrival.clear();
        CWorker.clear();

        FILE* fp;
        errno_t fal;
        string num = to_string(CMapNumber);
        CMapNo = "Map\\map000.txt";
        CMapNo.replace(10 - num.length(), num.length(), num);
        const char* file_name = CMapNo.c_str();

        fal = fopen_s(&fp, file_name, "r");

        if (!fal)
        {
            int row = 0, column = 0;
            int x = 0, y = 0;

            while (!feof(fp))
            {
                char c = fgetc(fp);

                if (c >= 32 || c == ' ' || c == '\t' || c == '\n')
                {
                    switch (c)
                    {
                    case '\t':
                        column++;
                        x += 8;
                        break;

                    case ' ':
                        column++;
                        x++;
                        break;


                    case '0':
                        column++;
                        x++;
                        break;

                    case '\n':
                        row++;
                        column = 0;
                        y++;
                        x = 0;
                        break;

                    case '\r':
                        row++;
                        column = 0;
                        y++;
                        x = 0;
                        break;

                    case 'H':
                        CWall.push_back(Coordinate(wall_character, y, x));
                        column++;
                        x++;
                        break;

                    case 'B':
                        CBox.push_back(Coordinate(box_character, y, x));
                        column++;
                        x++;
                        break;

                    case 'D':
                        CDest.push_back(Coordinate(dest_character, y, x));
                        column++;
                        x++;
                        break;

                    case 'C':
                        CBox.push_back(Coordinate(box_character, y, x));
                        CDest.push_back(Coordinate(dest_character, y, x));
                        column++;
                        x++;
                        break;

                    case 'W':
                        CWorker.push_back(Coordinate(worker_character, y, x));
                        column++;
                        x++;
                        break;
                    }

                    if (column > CCOLUMN)
                    {
                        CCOLUMN = column;
                    }

                    CROW = row;
                }
            }

            for (int i = -1; i <= CROW; i++)
            {
                for (int j = -1; j <= CCOLUMN; j++)
                {
                    CBlank.push_back(Coordinate(blank_character, i, j));
                }
            }

            fclose(fp);

            if (CBox.size() != CDest.size() || CWorker.size() != 1)
            {
                LoadMap(n + 1);
            }

            else
            {
                Arrive();
                return true;
            }
        }

        else
            return false;
    }

    else
        return false;
}