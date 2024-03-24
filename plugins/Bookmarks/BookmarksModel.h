/*
Copyright (C) 2017 - 2023 Evan Teran
						  evan.teran@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BOOKMARKS_MODEL_H_20170103_
#define BOOKMARKS_MODEL_H_20170103_

#include "Types.h"
#include <QAbstractItemModel>
#include <QVector>
#include <QIcon>

namespace BookmarksPlugin {

class BookmarksModel final : public QAbstractItemModel {
	Q_OBJECT

public:
	struct Bookmark {
		enum Type {
			Code,
			Data,
			Stack
		};

		edb::address_t address;
		Type type;
		QString comment;
	};

	static QString bookmarkTypeToString(Bookmark::Type type) {
		switch (type) {
		case Bookmark::Code:
			return tr("Code");
		case Bookmark::Data:
			return tr("Data");
		case Bookmark::Stack:
			return tr("Stack");
		}

		return tr("Code");
	}

	static Bookmark::Type bookmarkStringToType(const QString &type) {
		if (type == tr("Code")) {
			return Bookmark::Code;
		}

		if (type == tr("Data")) {
			return Bookmark::Data;
		}

		if (type == tr("Stack")) {
			return Bookmark::Stack;
		}

		return Bookmark::Code;
	}

public:
	explicit BookmarksModel(QObject *parent = nullptr);
	~BookmarksModel() override = default;

public:
	[[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	[[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	[[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;
	[[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	[[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	[[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public Q_SLOTS:
	void addBookmark(const Bookmark &r);
	void clearBookmarks();
	void deleteBookmark(const QModelIndex &index);
	void setComment(const QModelIndex &index, const QString &comment);
	void setType(const QModelIndex &index, const QString &type);
	void updateList();

public:
	[[nodiscard]] const QVector<Bookmark> &bookmarks() const { return bookmarks_; }

private:
	QVector<Bookmark> bookmarks_;
	QIcon breakpointIcon_;
	QIcon currentIcon_;
	QIcon currentBpIcon_;
};

}

#endif
