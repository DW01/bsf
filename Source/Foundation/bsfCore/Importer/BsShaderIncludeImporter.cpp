//************************************ bs::framework - Copyright 2018 Marko Pintera **************************************//
//*********** Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed. ***********//
#include "Importer/BsShaderIncludeImporter.h"
#include "Material/BsShaderInclude.h"
#include "FileSystem/BsDataStream.h"
#include "FileSystem/BsFileSystem.h"

namespace bs
{
	ShaderIncludeImporter::ShaderIncludeImporter()
		:SpecificImporter()
	{

	}

	ShaderIncludeImporter::~ShaderIncludeImporter()
	{

	}

	bool ShaderIncludeImporter::isExtensionSupported(const WString& ext) const
	{
		WString lowerCaseExt = ext;
		StringUtil::toLowerCase(lowerCaseExt);

		return lowerCaseExt == L"bslinc";
	}

	bool ShaderIncludeImporter::isMagicNumberSupported(const UINT8* magicNumPtr, UINT32 numBytes) const
	{
		return true; // Plain-text so I don't even check for magic number
	}

	SPtr<Resource> ShaderIncludeImporter::import(const Path& filePath, SPtr<const ImportOptions> importOptions)
	{
		String includeString;
		{
			Lock fileLock = FileScheduler::getLock(filePath);

			SPtr<DataStream> stream = FileSystem::openFile(filePath);
			includeString = stream->getAsString();
		}

		SPtr<ShaderInclude> gpuInclude = ShaderInclude::_createPtr(includeString);

		WString fileName = filePath.getWFilename(false);
		gpuInclude->setName(fileName);

		return gpuInclude;
	}
}