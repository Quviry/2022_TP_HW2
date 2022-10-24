#pragma once

namespace nvec{
	class RealContainer{
		public:
			RealContainer();
			~RealContainer();
			real get_value();
			RealContainer get_root();
			operator+()
		private:
			real containment;
	};
}