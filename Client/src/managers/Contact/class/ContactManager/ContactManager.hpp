#ifndef BABEL_CONTACTMANAGER_HPP_
# define BABEL_CONTACTMANAGER_HPP_

#include <vector>
#include "Status.hpp"
#include "Contact.hpp"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class ContactManager
	{
		public:
			ContactManager(babel::BabelClientManager&);
			virtual ~ContactManager();

		private:
			babel::BabelClientManager&		_root;
			babel::Contact					_user;
			std::vector<babel::Contact>		_contactList;


		public:
			const babel::BabelClientManager&	getRoot() const;
			babel::BabelClientManager&			getRoot();

			const babel::Contact&				getUser() const;
			babel::Contact&						getUser();

			const std::vector<babel::Contact>&	getContactList() const;
			std::vector<babel::Contact>&		getContactList();

			void setContactList(const std::vector<babel::Contact>&);
			void setUser(const babel::Contact&);

		public:
			const babel::Contact& getContactByLogin(const std::string&) const;
			babel::Contact& getContactByLogin(const std::string&);

			void updateContactList(const std::vector<babel::Contact>&);

			const babel::Status addContactByLogin(const std::string&);
			const babel::Status removeContactByLogin(const std::string&);
	};
}

#endif // !BABEL_CONTACTMANAGER_HPP_
