/*
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

#ifndef __ZLCONFIG_H__
#define __ZLCONFIG_H__

#include <string>

class ZLConfig;

class ZLConfigManager {

private:
	static ZLConfigManager &instance() {
		return *ourInstance;
	}

public:
	static void deleteInstance() {
		if (ourInstance != 0) {
			delete ourInstance;
		}
	}

protected:
	virtual ~ZLConfigManager();

private:
	virtual ZLConfig *createConfig() const = 0;

protected:
	static ZLConfigManager *ourInstance;

friend class ZLOptions;
};

class ZLConfig {

public:
	virtual ~ZLConfig();

	virtual void removeGroup(const std::string &name) = 0;

	virtual const std::string &getValue(const std::string &group, const std::string &name, const std::string &defaultValue) const = 0;
	virtual void setValue(const std::string &group, const std::string &name, const std::string &value, const std::string &category) = 0;
	virtual void unsetValue(const std::string &group, const std::string &name) = 0;

	virtual bool isAutoSavingSupported() const = 0;
	virtual void startAutoSave(int seconds) = 0;
};

#endif /* __ZLCONFIG_H__ */
