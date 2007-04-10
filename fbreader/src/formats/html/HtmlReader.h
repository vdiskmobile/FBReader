/*
 * FBReader -- electronic book reader
 * Copyright (C) 2004-2007 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __HTMLREADER_H__
#define __HTMLREADER_H__

#include <string>
#include <vector>

#include <ZLEncodingConverter.h>

class ZLInputStream;

class HtmlReader {

public:
	struct HtmlAttribute {
		std::string Name;
		std::string Value;
		bool hasValue;

		HtmlAttribute(const std::string &name);
		~HtmlAttribute();
		void setValue(const std::string &value);
	};

protected:
	struct HtmlTag {
		std::string Name;
		bool Start;
		std::vector<HtmlAttribute> Attributes;

		HtmlTag();
		~HtmlTag();
		void addAttribute(const std::string &name);
		void setLastAttributeValue(const std::string &value);

	private:
		HtmlTag(const HtmlTag&);
		const HtmlTag &operator= (const HtmlTag&);
	};

private:
	static void setTag(HtmlTag &tag, const std::string &fullName);

public:
	virtual void readDocument(ZLInputStream &stream);

protected:
	HtmlReader(const std::string &encoding);
	virtual ~HtmlReader();

protected:
	virtual void startDocumentHandler() = 0;
	virtual void endDocumentHandler() = 0;

	virtual bool tagHandler(const HtmlTag &tag) = 0;
	virtual bool characterDataHandler(const char *text, int len, bool convert) = 0;

private:
	void appendString(std::string &to, std::string &from);

protected:
	shared_ptr<ZLEncodingConverter> myConverter;
};

inline HtmlReader::HtmlAttribute::HtmlAttribute(const std::string &name) : Name(name), hasValue(false) {}
inline HtmlReader::HtmlAttribute::~HtmlAttribute() {}
inline void HtmlReader::HtmlAttribute::setValue(const std::string &value) { Value = value; hasValue = true; }

inline HtmlReader::HtmlTag::HtmlTag() : Start(true) {}
inline HtmlReader::HtmlTag::~HtmlTag() {}
inline void HtmlReader::HtmlTag::addAttribute(const std::string &name) { Attributes.push_back(HtmlAttribute(name)); }
inline void HtmlReader::HtmlTag::setLastAttributeValue(const std::string &value) { if (!Attributes.empty()) Attributes.back().setValue(value); }

#endif /* __HTMLREADER_H__ */
