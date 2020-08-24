void CMFC_OpenCVDlg::DrawImage(Mat mat, CWnd& picture)
{
	int bpp = 8 * mat.elemSize();

	int padding = 0;
	if (bpp < 32)
		padding = 4 - (mat.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	if (bpp < 32)
	{
		border = 4 - (mat.cols % 4);
	}

	Mat mat_temp;
	if (border > 0 || mat.isContinuous() == false)
	{
		cv::copyMakeBorder(mat, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat;
	}

	RECT r;
	picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	CImage image;
	image.Create(winSize.width, winSize.height, 24);

	BITMAPINFO *bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;

	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}

	if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
	{
		SetDIBitsToDevice(image.GetDC(),
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(image.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	HDC dc = ::GetDC(picture.m_hWnd);
	image.BitBlt(dc, 0, 0);

	::ReleaseDC(picture.m_hWnd, dc);

	image.ReleaseDC();
	image.Destroy();
}
