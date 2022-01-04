// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: contact.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_contact_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_contact_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_contact_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_contact_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_contact_2eproto;
namespace PhoneBookSerialize {
class Contact;
struct ContactDefaultTypeInternal;
extern ContactDefaultTypeInternal _Contact_default_instance_;
class ContactList;
struct ContactListDefaultTypeInternal;
extern ContactListDefaultTypeInternal _ContactList_default_instance_;
class Date;
struct DateDefaultTypeInternal;
extern DateDefaultTypeInternal _Date_default_instance_;
}  // namespace PhoneBookSerialize
PROTOBUF_NAMESPACE_OPEN
template<> ::PhoneBookSerialize::Contact* Arena::CreateMaybeMessage<::PhoneBookSerialize::Contact>(Arena*);
template<> ::PhoneBookSerialize::ContactList* Arena::CreateMaybeMessage<::PhoneBookSerialize::ContactList>(Arena*);
template<> ::PhoneBookSerialize::Date* Arena::CreateMaybeMessage<::PhoneBookSerialize::Date>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace PhoneBookSerialize {

// ===================================================================

class Date final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PhoneBookSerialize.Date) */ {
 public:
  inline Date() : Date(nullptr) {}
  ~Date() override;
  explicit constexpr Date(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Date(const Date& from);
  Date(Date&& from) noexcept
    : Date() {
    *this = ::std::move(from);
  }

  inline Date& operator=(const Date& from) {
    CopyFrom(from);
    return *this;
  }
  inline Date& operator=(Date&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Date& default_instance() {
    return *internal_default_instance();
  }
  static inline const Date* internal_default_instance() {
    return reinterpret_cast<const Date*>(
               &_Date_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Date& a, Date& b) {
    a.Swap(&b);
  }
  inline void Swap(Date* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Date* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Date* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Date>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Date& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Date& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Date* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PhoneBookSerialize.Date";
  }
  protected:
  explicit Date(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDayFieldNumber = 1,
    kMonthFieldNumber = 2,
    kYearFieldNumber = 3,
  };
  // uint32 day = 1;
  void clear_day();
  uint32_t day() const;
  void set_day(uint32_t value);
  private:
  uint32_t _internal_day() const;
  void _internal_set_day(uint32_t value);
  public:

  // uint32 month = 2;
  void clear_month();
  uint32_t month() const;
  void set_month(uint32_t value);
  private:
  uint32_t _internal_month() const;
  void _internal_set_month(uint32_t value);
  public:

  // uint64 year = 3;
  void clear_year();
  uint64_t year() const;
  void set_year(uint64_t value);
  private:
  uint64_t _internal_year() const;
  void _internal_set_year(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:PhoneBookSerialize.Date)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint32_t day_;
  uint32_t month_;
  uint64_t year_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_contact_2eproto;
};
// -------------------------------------------------------------------

class Contact final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PhoneBookSerialize.Contact) */ {
 public:
  inline Contact() : Contact(nullptr) {}
  ~Contact() override;
  explicit constexpr Contact(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Contact(const Contact& from);
  Contact(Contact&& from) noexcept
    : Contact() {
    *this = ::std::move(from);
  }

  inline Contact& operator=(const Contact& from) {
    CopyFrom(from);
    return *this;
  }
  inline Contact& operator=(Contact&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Contact& default_instance() {
    return *internal_default_instance();
  }
  static inline const Contact* internal_default_instance() {
    return reinterpret_cast<const Contact*>(
               &_Contact_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Contact& a, Contact& b) {
    a.Swap(&b);
  }
  inline void Swap(Contact* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Contact* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Contact* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Contact>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Contact& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Contact& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Contact* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PhoneBookSerialize.Contact";
  }
  protected:
  explicit Contact(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPhoneNumberFieldNumber = 3,
    kNameFieldNumber = 1,
    kBirthdayFieldNumber = 2,
  };
  // repeated string phone_number = 3;
  int phone_number_size() const;
  private:
  int _internal_phone_number_size() const;
  public:
  void clear_phone_number();
  const std::string& phone_number(int index) const;
  std::string* mutable_phone_number(int index);
  void set_phone_number(int index, const std::string& value);
  void set_phone_number(int index, std::string&& value);
  void set_phone_number(int index, const char* value);
  void set_phone_number(int index, const char* value, size_t size);
  std::string* add_phone_number();
  void add_phone_number(const std::string& value);
  void add_phone_number(std::string&& value);
  void add_phone_number(const char* value);
  void add_phone_number(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& phone_number() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_phone_number();
  private:
  const std::string& _internal_phone_number(int index) const;
  std::string* _internal_add_phone_number();
  public:

  // string name = 1;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // .PhoneBookSerialize.Date birthday = 2;
  bool has_birthday() const;
  private:
  bool _internal_has_birthday() const;
  public:
  void clear_birthday();
  const ::PhoneBookSerialize::Date& birthday() const;
  PROTOBUF_NODISCARD ::PhoneBookSerialize::Date* release_birthday();
  ::PhoneBookSerialize::Date* mutable_birthday();
  void set_allocated_birthday(::PhoneBookSerialize::Date* birthday);
  private:
  const ::PhoneBookSerialize::Date& _internal_birthday() const;
  ::PhoneBookSerialize::Date* _internal_mutable_birthday();
  public:
  void unsafe_arena_set_allocated_birthday(
      ::PhoneBookSerialize::Date* birthday);
  ::PhoneBookSerialize::Date* unsafe_arena_release_birthday();

  // @@protoc_insertion_point(class_scope:PhoneBookSerialize.Contact)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> phone_number_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PhoneBookSerialize::Date* birthday_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_contact_2eproto;
};
// -------------------------------------------------------------------

class ContactList final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PhoneBookSerialize.ContactList) */ {
 public:
  inline ContactList() : ContactList(nullptr) {}
  ~ContactList() override;
  explicit constexpr ContactList(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ContactList(const ContactList& from);
  ContactList(ContactList&& from) noexcept
    : ContactList() {
    *this = ::std::move(from);
  }

  inline ContactList& operator=(const ContactList& from) {
    CopyFrom(from);
    return *this;
  }
  inline ContactList& operator=(ContactList&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ContactList& default_instance() {
    return *internal_default_instance();
  }
  static inline const ContactList* internal_default_instance() {
    return reinterpret_cast<const ContactList*>(
               &_ContactList_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(ContactList& a, ContactList& b) {
    a.Swap(&b);
  }
  inline void Swap(ContactList* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ContactList* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ContactList* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ContactList>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ContactList& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ContactList& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ContactList* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PhoneBookSerialize.ContactList";
  }
  protected:
  explicit ContactList(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kContactsFieldNumber = 1,
  };
  // repeated .PhoneBookSerialize.Contact contacts = 1;
  int contacts_size() const;
  private:
  int _internal_contacts_size() const;
  public:
  void clear_contacts();
  ::PhoneBookSerialize::Contact* mutable_contacts(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PhoneBookSerialize::Contact >*
      mutable_contacts();
  private:
  const ::PhoneBookSerialize::Contact& _internal_contacts(int index) const;
  ::PhoneBookSerialize::Contact* _internal_add_contacts();
  public:
  const ::PhoneBookSerialize::Contact& contacts(int index) const;
  ::PhoneBookSerialize::Contact* add_contacts();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PhoneBookSerialize::Contact >&
      contacts() const;

  // @@protoc_insertion_point(class_scope:PhoneBookSerialize.ContactList)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PhoneBookSerialize::Contact > contacts_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_contact_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Date

// uint32 day = 1;
inline void Date::clear_day() {
  day_ = 0u;
}
inline uint32_t Date::_internal_day() const {
  return day_;
}
inline uint32_t Date::day() const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Date.day)
  return _internal_day();
}
inline void Date::_internal_set_day(uint32_t value) {
  
  day_ = value;
}
inline void Date::set_day(uint32_t value) {
  _internal_set_day(value);
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Date.day)
}

// uint32 month = 2;
inline void Date::clear_month() {
  month_ = 0u;
}
inline uint32_t Date::_internal_month() const {
  return month_;
}
inline uint32_t Date::month() const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Date.month)
  return _internal_month();
}
inline void Date::_internal_set_month(uint32_t value) {
  
  month_ = value;
}
inline void Date::set_month(uint32_t value) {
  _internal_set_month(value);
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Date.month)
}

// uint64 year = 3;
inline void Date::clear_year() {
  year_ = uint64_t{0u};
}
inline uint64_t Date::_internal_year() const {
  return year_;
}
inline uint64_t Date::year() const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Date.year)
  return _internal_year();
}
inline void Date::_internal_set_year(uint64_t value) {
  
  year_ = value;
}
inline void Date::set_year(uint64_t value) {
  _internal_set_year(value);
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Date.year)
}

// -------------------------------------------------------------------

// Contact

// string name = 1;
inline void Contact::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& Contact::name() const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Contact.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Contact::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Contact.name)
}
inline std::string* Contact::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:PhoneBookSerialize.Contact.name)
  return _s;
}
inline const std::string& Contact::_internal_name() const {
  return name_.Get();
}
inline void Contact::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Contact::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Contact::release_name() {
  // @@protoc_insertion_point(field_release:PhoneBookSerialize.Contact.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Contact::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (name_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:PhoneBookSerialize.Contact.name)
}

// .PhoneBookSerialize.Date birthday = 2;
inline bool Contact::_internal_has_birthday() const {
  return this != internal_default_instance() && birthday_ != nullptr;
}
inline bool Contact::has_birthday() const {
  return _internal_has_birthday();
}
inline void Contact::clear_birthday() {
  if (GetArenaForAllocation() == nullptr && birthday_ != nullptr) {
    delete birthday_;
  }
  birthday_ = nullptr;
}
inline const ::PhoneBookSerialize::Date& Contact::_internal_birthday() const {
  const ::PhoneBookSerialize::Date* p = birthday_;
  return p != nullptr ? *p : reinterpret_cast<const ::PhoneBookSerialize::Date&>(
      ::PhoneBookSerialize::_Date_default_instance_);
}
inline const ::PhoneBookSerialize::Date& Contact::birthday() const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Contact.birthday)
  return _internal_birthday();
}
inline void Contact::unsafe_arena_set_allocated_birthday(
    ::PhoneBookSerialize::Date* birthday) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(birthday_);
  }
  birthday_ = birthday;
  if (birthday) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:PhoneBookSerialize.Contact.birthday)
}
inline ::PhoneBookSerialize::Date* Contact::release_birthday() {
  
  ::PhoneBookSerialize::Date* temp = birthday_;
  birthday_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::PhoneBookSerialize::Date* Contact::unsafe_arena_release_birthday() {
  // @@protoc_insertion_point(field_release:PhoneBookSerialize.Contact.birthday)
  
  ::PhoneBookSerialize::Date* temp = birthday_;
  birthday_ = nullptr;
  return temp;
}
inline ::PhoneBookSerialize::Date* Contact::_internal_mutable_birthday() {
  
  if (birthday_ == nullptr) {
    auto* p = CreateMaybeMessage<::PhoneBookSerialize::Date>(GetArenaForAllocation());
    birthday_ = p;
  }
  return birthday_;
}
inline ::PhoneBookSerialize::Date* Contact::mutable_birthday() {
  ::PhoneBookSerialize::Date* _msg = _internal_mutable_birthday();
  // @@protoc_insertion_point(field_mutable:PhoneBookSerialize.Contact.birthday)
  return _msg;
}
inline void Contact::set_allocated_birthday(::PhoneBookSerialize::Date* birthday) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete birthday_;
  }
  if (birthday) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::PhoneBookSerialize::Date>::GetOwningArena(birthday);
    if (message_arena != submessage_arena) {
      birthday = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, birthday, submessage_arena);
    }
    
  } else {
    
  }
  birthday_ = birthday;
  // @@protoc_insertion_point(field_set_allocated:PhoneBookSerialize.Contact.birthday)
}

// repeated string phone_number = 3;
inline int Contact::_internal_phone_number_size() const {
  return phone_number_.size();
}
inline int Contact::phone_number_size() const {
  return _internal_phone_number_size();
}
inline void Contact::clear_phone_number() {
  phone_number_.Clear();
}
inline std::string* Contact::add_phone_number() {
  std::string* _s = _internal_add_phone_number();
  // @@protoc_insertion_point(field_add_mutable:PhoneBookSerialize.Contact.phone_number)
  return _s;
}
inline const std::string& Contact::_internal_phone_number(int index) const {
  return phone_number_.Get(index);
}
inline const std::string& Contact::phone_number(int index) const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.Contact.phone_number)
  return _internal_phone_number(index);
}
inline std::string* Contact::mutable_phone_number(int index) {
  // @@protoc_insertion_point(field_mutable:PhoneBookSerialize.Contact.phone_number)
  return phone_number_.Mutable(index);
}
inline void Contact::set_phone_number(int index, const std::string& value) {
  phone_number_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::set_phone_number(int index, std::string&& value) {
  phone_number_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::set_phone_number(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  phone_number_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::set_phone_number(int index, const char* value, size_t size) {
  phone_number_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PhoneBookSerialize.Contact.phone_number)
}
inline std::string* Contact::_internal_add_phone_number() {
  return phone_number_.Add();
}
inline void Contact::add_phone_number(const std::string& value) {
  phone_number_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::add_phone_number(std::string&& value) {
  phone_number_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::add_phone_number(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  phone_number_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:PhoneBookSerialize.Contact.phone_number)
}
inline void Contact::add_phone_number(const char* value, size_t size) {
  phone_number_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:PhoneBookSerialize.Contact.phone_number)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Contact::phone_number() const {
  // @@protoc_insertion_point(field_list:PhoneBookSerialize.Contact.phone_number)
  return phone_number_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Contact::mutable_phone_number() {
  // @@protoc_insertion_point(field_mutable_list:PhoneBookSerialize.Contact.phone_number)
  return &phone_number_;
}

// -------------------------------------------------------------------

// ContactList

// repeated .PhoneBookSerialize.Contact contacts = 1;
inline int ContactList::_internal_contacts_size() const {
  return contacts_.size();
}
inline int ContactList::contacts_size() const {
  return _internal_contacts_size();
}
inline void ContactList::clear_contacts() {
  contacts_.Clear();
}
inline ::PhoneBookSerialize::Contact* ContactList::mutable_contacts(int index) {
  // @@protoc_insertion_point(field_mutable:PhoneBookSerialize.ContactList.contacts)
  return contacts_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PhoneBookSerialize::Contact >*
ContactList::mutable_contacts() {
  // @@protoc_insertion_point(field_mutable_list:PhoneBookSerialize.ContactList.contacts)
  return &contacts_;
}
inline const ::PhoneBookSerialize::Contact& ContactList::_internal_contacts(int index) const {
  return contacts_.Get(index);
}
inline const ::PhoneBookSerialize::Contact& ContactList::contacts(int index) const {
  // @@protoc_insertion_point(field_get:PhoneBookSerialize.ContactList.contacts)
  return _internal_contacts(index);
}
inline ::PhoneBookSerialize::Contact* ContactList::_internal_add_contacts() {
  return contacts_.Add();
}
inline ::PhoneBookSerialize::Contact* ContactList::add_contacts() {
  ::PhoneBookSerialize::Contact* _add = _internal_add_contacts();
  // @@protoc_insertion_point(field_add:PhoneBookSerialize.ContactList.contacts)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PhoneBookSerialize::Contact >&
ContactList::contacts() const {
  // @@protoc_insertion_point(field_list:PhoneBookSerialize.ContactList.contacts)
  return contacts_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace PhoneBookSerialize

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_contact_2eproto
