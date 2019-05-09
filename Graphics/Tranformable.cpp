#include "Tranformable.h"

namespace yuh {
	namespace graphics {

		Tranformable::Tranformable() :
			m_needUpdate(true),
			m_scale(1, 1, 1)
		{
		}

		Tranformable::~Tranformable()
		{
		}

		Tranformable & Tranformable::translate(const Vec3f & trans)
		{
			m_position += trans;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::scale(const Vec3f & scale)
		{
			m_scale += scale;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::rotate(const Vec3f & rotate)
		{
			m_rotate += rotate;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::setOrigin(const Vec3f & vec)
		{
			m_origin = vec;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::setPosition(const Vec3f & vec)
		{
			m_position = vec;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::setScale(const Vec3f & vec)
		{
			m_scale = vec;
			m_needUpdate = true;
			return *this;
		}

		Tranformable & Tranformable::setRotate(const Vec3f & vec)
		{
			m_rotate = vec;
			m_needUpdate = true;
			return *this;
		}

		Vec3f Tranformable::getOrigin()
		{
			return m_origin;
		}

		Vec3f Tranformable::getScale()
		{
			return m_scale;
		}

		Vec3f Tranformable::getRotate()
		{
			return m_rotate;
		}

		Vec3f Tranformable::getPosition()
		{
			return m_position;
		}

		Tranformable & Tranformable::update()
		{
			if (m_needUpdate) {
				m_tranform = 
					AffineTranslate(m_position) *
					AffineRotate(1.0, m_rotate) *
					AffineScale(m_scale) *
					AffineTranslate(m_origin);
				m_needUpdate = false;
			}
			return *this;
		}

		Mat4f Tranformable::getMat4()
		{
			update();
			return m_tranform;
		}

		Tranformable::operator const float*()
		{
			update();
			return m_tranform.getPtr();
		}

		const float * Tranformable::getPtr()
		{
			update();
			return m_tranform.getPtr();
		}

	}
}